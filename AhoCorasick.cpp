/*
Time limit	12.5 seconds
Memory limit	30.0 MB
Input	stdin or input.txt
Output	stdout or output.txt

problem :
8 years after the conclusion of the war, Naruto became the Hokage of the Hidden Leaf village.
Usually he receives a lot of messages every day, but today he received a very strange text from an unknown person.
Nobody from the Hidden Leaf village understands the text, so he needs to decode it. To do it, 
he needs to find the positions of all occurrences of a specific pattern of length m (m <= 5000) in the text of length n (n <= 2000000). 
But there is something special about this pattern — the characters “?” can occur in this pattern. Each occurrence assumes that all the usual characters match the corresponding ones from the text, 
and instead of the symbol “?”, there is an arbitrary character in the text. It is guaranteed that “?” does not occur in the text.

Your task is to help Naruto find all the positions of all occurrences of this pattern. Also, 
Naruto wants an algorithm with time complexity O(m+n+t), where t is the total number of occurrences of that pattern.

Input format
The first line contains the pattern with length m (m <= 5000).
The second line contains the text with length n (n <= 2000000).

Sample 1
Input	                          Output
ab??aba                           2
ababacaba

Sample 2
Input	                          Output
aa??bab?cbaa?                    0 13
aabbbabbcbaabaabbbabbcbaab                               
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
  std::unordered_map<char, Node*> children;
  std::vector<std::pair<unsigned, unsigned>> index;
  Node *fail, *next_fail;

  Node() : fail(nullptr), next_fail(nullptr) {}
};

class AhoCorasick {
 public:
  AhoCorasick(std::vector<std::pair<std::string, unsigned>>& patterns_);
  ~AhoCorasick();
  void DeleteTrie(Node* root_);
  void BuildTrie();
  void FailureFunction();
  Node* GetFail(Node* node);
  std::vector<int> Search(const std::string& text);

 private:
  Node* root_;
  std::vector<std::pair<std::string, unsigned>>& patterns_;
};

AhoCorasick::AhoCorasick(
    std::vector<std::pair<std::string, unsigned>>& patterns_)
    : patterns_(patterns_) {
  BuildTrie();
  FailureFunction();
}

AhoCorasick::~AhoCorasick() { DeleteTrie(root_); }

void AhoCorasick::DeleteTrie(Node* root) {
  std::stack<Node*> stack;
  stack.push(root);

  while (!stack.empty()) {
    Node* current = stack.top();
    stack.pop();

    for (auto& pair : current->children) {
      stack.push(pair.second);
    }

    delete current;
  }
}

void AhoCorasick::BuildTrie() {
  root_ = new Node();
  for (unsigned i = 0; i < patterns_.size(); i++) {
    Node* curr = root_;
    for (char c : patterns_[i].first) {
      if (!curr->children[c]) {
        curr->children[c] = new Node();
      }
      curr = curr->children[c];
    }
    curr->index.push_back({patterns_[i].second, i});
  }
}

void AhoCorasick::FailureFunction() {
  std::queue<Node*> queue;
  for (auto& kvp : root_->children) {
    queue.push(kvp.second);
    kvp.second->fail = root_;
    while (!queue.empty()) {
      Node* curr = queue.front();
      queue.pop();

      for (auto& kvp : curr->children) {
        char c = kvp.first;
        Node* child = kvp.second;
        queue.push(child);
        Node* start = curr->fail;
        while (start != nullptr && !start->children.count(c)) {
          start = start->fail;
        }
        if (start != nullptr) {
          child->fail = start->children[c];
        } else {
          child->fail = root_;
        }
      }
    }
  }
}

Node* AhoCorasick::GetFail(Node* node) {
  if (node->next_fail == nullptr) {
    auto next_node = node->fail;
    if (next_node != root_) {
      node->next_fail =
          next_node->index.empty() ? GetFail(next_node) : next_node;
    } else {
      node->next_fail = root_;
    }
  }
  return node->next_fail;
}

std::vector<int> AhoCorasick::Search(const std::string& text) {
  std::vector<int> matches(text.size(), 0);
  Node* curr = root_;
  for (unsigned i = 0; i < text.size(); ++i) {
    char c = text[i];
    while (curr != root_ && !curr->children.count(c)) {
      curr = curr->fail;
    }
    if (curr->children.count(c)) {
      curr = curr->children[c];
    }
    Node* temp = curr;
    while (temp != root_) {
      for (std::pair index : temp->index) {
        if (index.first <= i) {
          matches[i - index.first]++;
        }
      }
      temp = GetFail(temp);
    }
  }

  return matches;
}

std::vector<std::pair<std::string, unsigned>> SplitPattern(
    const std::string& pattern) {
  std::vector<std::pair<std::string, unsigned>> segments;
  std::string segment = "";

  for (unsigned i = 0; i < pattern.size(); i++) {
    if (pattern[i] == '?') {
      if (!segment.empty()) {
        segments.push_back({segment, i - 1});
        segment = "";
      }

    } else {
      segment += pattern[i];
    }
  }

  if (!segment.empty()) {
    segments.push_back({segment, pattern.size() - 1});
  }

  return segments;
}

void CombineMatches(
    const std::string& text, const std::string& pattern,
    const std::vector<int>& index_pos,
    const std::vector<std::pair<std::string, unsigned>> segments) {
  unsigned pattern_size = pattern.size();
  unsigned text_size = text.size();
  int segments_size = segments.size();
  for (unsigned i = 0; i < index_pos.size(); i++) {
    if (i + pattern_size <= text_size && index_pos[i] == segments_size) {
      std::cout << i << " ";
    }
  }
}

int main() {
  std::string pattern, text;
  std::cin >> pattern >> text;
  std::vector<std::pair<std::string, unsigned>> segments =
      SplitPattern(pattern);
  AhoCorasick corasick(segments);
  std::vector<int> index_pos = corasick.Search(text);
  CombineMatches(text, pattern, index_pos, segments);
  return 0;
}
