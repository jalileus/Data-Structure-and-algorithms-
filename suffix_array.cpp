#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int Alphapet = 256;

class SuffixArray {
 public:
  SuffixArray(const std::string& str);
  ~SuffixArray();
  std::vector<int> GetLcp() const;
  std::vector<int> ToIntArray(const std::string& str);
  void Construct();
  void FrequencyAndCount();
  void CountingSort();
  void Kasai();
  std::vector<int> lcp_;

 private:
  int n_;
  std::vector<int> sa_, sa_2_, rank_, temp_, freq_count_, text_;
};

SuffixArray::SuffixArray(const std::string& str) {
  text_ = ToIntArray(str);
  n_ = text_.size();
  sa_.resize(n_);

  sa_2_.resize(n_);
  rank_.resize(n_);
  freq_count_.resize(std::max(Alphapet, n_));
  Construct();
  Kasai();
}

SuffixArray::~SuffixArray() {}

std::vector<int> SuffixArray::GetLcp() const { return lcp_; }

std::vector<int> SuffixArray::ToIntArray(const std::string& str) {
  std::vector<int> text(str.length());
  for (unsigned i = 0; i < str.length(); i++) {
    text[i] = str[i];
  }
  return text;
}

void SuffixArray::FrequencyAndCount() {
  int i;
  for (i = 0; i < n_; i++) {
    freq_count_[rank_[i] = text_[i]]++;
  }
  for (i = 1; i < Alphapet; i++) {
    freq_count_[i] += freq_count_[i - 1];
  }
  for (i = n_ - 1; i >= 0; i--) {
    sa_[--freq_count_[text_[i]]] = i;
  }
}

void SuffixArray::CountingSort() {
  int i;
  std::fill(freq_count_.begin(), freq_count_.begin() + Alphapet, 0);
  for (i = 0; i < n_; i++) {
    freq_count_[rank_[i]]++;
  }
  for (i = 1; i < Alphapet; i++) {
    freq_count_[i] += freq_count_[i - 1];
  }
  for (i = n_ - 1; i >= 0; i--) {
    sa_[--freq_count_[rank_[sa_2_[i]]]] = sa_2_[i];
  }
}

void SuffixArray::Construct() {
  int i, p, r;
  FrequencyAndCount();
  for (p = 1; p < n_; p <<= 1) {
    for (r = 0, i = n_ - p; i < n_; i++) {
      sa_2_[r++] = i;
    }
    for (i = 0; i < n_; i++) {
      if (sa_[i] >= p) {
        sa_2_[r++] = sa_[i] - p;
      }
    }
    CountingSort();
    for (sa_2_[sa_[0]] = r = 0, i = 1; i < n_; i++) {
      if (!(rank_[sa_[i - 1]] == rank_[sa_[i]] && sa_[i - 1] + p < n_ &&
            sa_[i] + p < n_ && rank_[sa_[i - 1] + p] == rank_[sa_[i] + p])) {
        r++;
      }
      sa_2_[sa_[i]] = r;
    }
    temp_ = rank_;
    rank_ = sa_2_;
    sa_2_ = temp_;
    if (r == n_ - 1) {
      break;
    }
    Alphapet = r + 1;
  }
}

void SuffixArray::Kasai() {
  lcp_.resize(n_);
  std::vector<int> inv(n_);
  for (int i = 0; i < n_; i++) {
    inv[sa_[i]] = i;
  }
  for (int i = 0, len = 0; i < n_; i++) {
    if (inv[i] > 0) {
      int k = sa_[inv[i] - 1];
      while ((i + len < n_) && (k + len < n_) &&
             text_[i + len] == text_[k + len]) {
        len++;
      }
      lcp_[inv[i] - 1] = len;
      if (len > 0) {
        len--;
      }
    }
  }
}

int main() {
  std::string text;
  std::cin >> text;
  SuffixArray my_array(text);
  int dub = 0;
  for (unsigned i = 0; i < my_array.lcp_.size(); i++) {
    dub += my_array.lcp_[i];
  }
  int size = text.length();
  int total_suffixes = (size * (size + 1)) / 2;
  int res = total_suffixes - dub;
  std::cout << res << std::endl;
  return 0;
}