/*
Time limit	0.057 seconds
Memory limit	2.0 MB
Input	stdin or input.txt
Output	stdout or output.txt

problem :
Given a string of length n. Find the total number of its distinct substrings. Use a suffix array. Constructing a suffix array takes O(nlogn). 
Calculate the number of distinct substrings in O(n)

Input format
A string of length <= 40000

Sample
Input	                              Output
wsmmumrvpvvusnuxzomuouyyvxv          362

*/


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int kAlphabetSize = 256;

class SuffixArray {
 public:
  SuffixArray(const std::string& str);
  ~SuffixArray();
  std::vector<int> GetLcp() const;
  std::vector<int> ConvertToIntegerArray(const std::string& str);
  void ConstructSuffixArray();
  void InitializeFrequencyAndCount();
  void PerformCountingSort();
  void ComputeLcpArray();
  std::vector<int> lcp_array_;

 private:
  int text_length_;
  std::vector<int> suffix_array_, temp_suffix_array_, rank_, temp_rank_, frequency_count_, text_;
};

SuffixArray::SuffixArray(const std::string& str) {
  text_ = ConvertToIntegerArray(str);
  text_length_ = text_.size();
  suffix_array_.resize(text_length_);

  temp_suffix_array_.resize(text_length_);
  rank_.resize(text_length_);
  frequency_count_.resize(std::max(kAlphabetSize, text_length_));
  ConstructSuffixArray();
  ComputeLcpArray();
}

SuffixArray::~SuffixArray() {}

std::vector<int> SuffixArray::GetLcp() const { return lcp_array_; }

std::vector<int> SuffixArray::ConvertToIntegerArray(const std::string& str) {
  std::vector<int> text(str.length());
  for (unsigned i = 0; i < str.length(); i++) {
    text[i] = static_cast<int>(str[i]);
  }
  return text;
}

void SuffixArray::InitializeFrequencyAndCount() {
  int i;
  for (i = 0; i < text_length_; i++) {
    frequency_count_[rank_[i] = text_[i]]++;
  }
  for (i = 1; i < kAlphabetSize; i++) {
    frequency_count_[i] += frequency_count_[i - 1];
  }
  for (i = text_length_ - 1; i >= 0; i--) {
    suffix_array_[--frequency_count_[text_[i]]] = i;
  }
}

void SuffixArray::PerformCountingSort() {
  int i;
  std::fill(frequency_count_.begin(), frequency_count_.begin() + kAlphabetSize, 0);
  for (i = 0; i < text_length_; i++) {
    frequency_count_[rank_[i]]++;
  }
  for (i = 1; i < kAlphabetSize; i++) {
    frequency_count_[i] += frequency_count_[i - 1];
  }
  for (i = text_length_ - 1; i >= 0; i--) {
    suffix_array_[--frequency_count_[rank_[temp_suffix_array_[i]]]] = temp_suffix_array_[i];
  }
}

void SuffixArray::ConstructSuffixArray() {
  int i, p, r;
  InitializeFrequencyAndCount();
  for (p = 1; p < text_length_; p <<= 1) {
    for (r = 0, i = text_length_ - p; i < text_length_; i++) {
      temp_suffix_array_[r++] = i;
    }
    for (i = 0; i < text_length_; i++) {
      if (suffix_array_[i] >= p) {
        temp_suffix_array_[r++] = suffix_array_[i] - p;
      }
    }
    PerformCountingSort();
    for (temp_suffix_array_[suffix_array_[0]] = r = 0, i = 1; i < text_length_; i++) {
      if (!(rank_[suffix_array_[i - 1]] == rank_[suffix_array_[i]] && suffix_array_[i - 1] + p < text_length_ &&
            suffix_array_[i] + p < text_length_ && rank_[suffix_array_[i - 1] + p] == rank_[suffix_array_[i] + p])) {
        r++;
      }
      temp_suffix_array_[suffix_array_[i]] = r;
    }
    temp_rank_ = rank_;
    rank_ = temp_suffix_array_;
    temp_suffix_array_ = temp_rank_;
    if (r == text_length_ - 1) {
      break;
    }
    kAlphabetSize = r + 1;
  }
}

void SuffixArray::ComputeLcpArray() {
  lcp_array_.resize(text_length_);
  std::vector<int> inverse_suffix_array(text_length_);
  for (int i = 0; i < text_length_; i++) {
    inverse_suffix_array[suffix_array_[i]] = i;
  }
  for (int i = 0, len = 0; i < text_length_; i++) {
    if (inverse_suffix_array[i] > 0) {
      int k = suffix_array_[inverse_suffix_array[i] - 1];
      while ((i + len < text_length_) && (k + len < text_length_) &&
             text_[i + len] == text_[k + len]) {
        len++;
      }
      lcp_array_[inverse_suffix_array[i] - 1] = len;
      if (len > 0) {
        len--;
      }
    }
  }
}

int main() {
  std::string text;
  std::cin >> text;
  SuffixArray suffix_array(text);
  int sum_lcp = 0;
  for (unsigned i = 0; i < suffix_array.lcp_array_.size(); i++) {
    sum_lcp += suffix_array.lcp_array_[i];
  }
  int text_size = text.length();
  int total_suffixes = (text_size * (text_size + 1)) / 2;
  int result = total_suffixes - sum_lcp;
  std::cout << result << std::endl;
  return 0;
}
