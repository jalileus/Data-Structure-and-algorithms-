/*
NOTE!!!: THIS CODE IMPLEMENT ## BronKerbosch ## ALGORITHM

Time limit	5 seconds
Memory limit	790.7 MB
Input	stdin or input.txt
Output	stdout or output.txt

problem :
After another hard day at MIPT, you come to the dormitory. But there's trouble! Cockroaches have eaten all your food again.
You have olny one trap to defeat this evil. So you decided to number the cockroaches starting from 0 and make a list of each cockroach's friends. Since the cockroaches are very friendly, 
you decided to poison the largest group of cockroaches, where all cockroaches are friends with each other.

Input format:
Let N be the number of cockroaches (0 < N < 53), and given a symmetric matrix a of size N×N, where a_ij = 1 means that cockroach i is friends with cockroach j, or a_ij = 0 otherwise.

Output format:
Print the numbers of cockroaches from this group, separated by spaces, in ascending order.

Sample
Input	            Output
5                 1 2 3
0 1 0 0 1
1 0 1 1 0
0 1 0 1 0
0 1 1 0 0
1 0 0 0 0

Notes
It is guaranteed that there is only one friendly cockroach group of maximum size

*/

#include <algorithm>
#include <iostream>
#include <vector>

unsigned long long max_size = 0;
std::vector<int> max_clique;

void PrintVector() {
  std::sort(max_clique.begin(), max_clique.end());
  for (unsigned long i = 0; i < max_clique.size(); i++) {
    std::cout << max_clique[i] << " ";
  }
  std::cout << std::endl;
}

void BronKerbosch(std::vector<std::vector<int>>& graph, std::vector<int>& r,
                  std::vector<int>& p, std::vector<int>& x) {
  if (p.empty() && x.empty()) {
    if (r.size() > max_size) {
      max_size = r.size();
      max_clique = r;
    }
    return;
  }
  int pivot = p.empty() ? x[0] : p[0];
  for (int vertex : p) {
    if (graph[pivot][vertex] == 1) {
      continue;
    }
    r.push_back(vertex);
    std::vector<int> new_p, new_x;
    for (int neighbor : p) {
      if (graph[vertex][neighbor] == 1) {
        new_p.push_back(neighbor);
      }
    }
    for (int neighbor : x) {
      if (graph[vertex][neighbor] == 1) {
        new_x.push_back(neighbor);
      }
    }
    BronKerbosch(graph, r, new_p, new_x);
    p.erase(std::find(p.begin(), p.end(), vertex));
    x.push_back(vertex);
    r.pop_back();
  }
}

class Graph {
 public:
  Graph(int n, std::vector<std::vector<int>>& graph);
  void GetMaxClique();

 private:
  int v_;
  std::vector<std::vector<int>> adj_;
  std::vector<int> r_, p_, x_;
};

Graph::Graph(int n, std::vector<std::vector<int>>& graph) : v_(n), adj_(graph) {
  for (int i = 0; i < n; i++) {
    p_.push_back(i);
  }
}

void Graph::GetMaxClique() { BronKerbosch(adj_, r_, p_, x_); }

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> graph[i][j];
    }
  }
  Graph my_graph(n, graph);
  my_graph.GetMaxClique();
  PrintVector();
  return 0;
}
