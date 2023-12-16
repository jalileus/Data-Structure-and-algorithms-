#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

std::vector<int> quick_table;
std::vector<std::vector<int>> dp;
std::vector<std::vector<int>> index_dp;

void BuildMinSparseTable(std::vector<int>& values) {
  unsigned int n = values.size();
  int p = std::floor(std::log2(n));
  unsigned int size = p + 1;
  dp.resize(size, std::vector<int>(n));
  index_dp.resize(size, std::vector<int>(n));
  quick_table.resize(n + 1, 0);
  for (unsigned int i = 2; i <= n; i++) {
    quick_table[i] = quick_table[i / 2] + 1;
  }
  for (unsigned int i = 0; i < n; i++) {
    dp[0][i] = values[i];
    index_dp[0][i] = i;
  }
  for (int i = 1; i <= p; i++) {
    for (unsigned int j = 0; j + (1 << i) <= n; j++) {
      int left = dp[i - 1][j];
      int right = dp[i - 1][j + (1 << (i - 1))];
      dp[i][j] = std::min(left, right);
      if (left <= right) {
        index_dp[i][j] = index_dp[i - 1][j];
      } else {
        index_dp[i][j] = index_dp[i - 1][j + (1 << (i - 1))];
      }
    }
  }
}

int GetIndex(int l, int r) {
  int length = r - l + 1;
  int p = quick_table[length];
  int left = dp[p][l];
  int right = dp[p][r - (1 << p) + 1];
  if (left <= right) {
    return index_dp[p][l];
  }
  return index_dp[p][r - (1 << p) + 1];
}

int MinQuery(int l, int r) {
  int length = r - l + 1;
  int p = quick_table[length];
  int left = dp[p][l];
  int right = dp[p][r - (1 << p) + 1];
  return std::min(left, right);
}

int GetSecondStatistic(int l, int r) {
  int index = GetIndex(l, r);
  if (l == index) {
    return MinQuery(1 + index, r);
  }
  if (r == index) {
    return MinQuery(l, index - 1);
  }
  int left = MinQuery(l, index - 1);
  int right = MinQuery(1 + index, r);
  int second = std::min(left, right);
  return second;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> values(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i];
  }
  BuildMinSparseTable(values);
  for (int j = 0; j < m; j++) {
    int l, r;
    std::cin >> l >> r;
    std::cout << GetSecondStatistic(l - 1, r - 1) << std::endl;
  }
  return 0;
}