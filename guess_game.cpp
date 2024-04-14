#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int GetMinCost(int n, std::vector<std::vector<int>> dp) {
  for (int l = 2; l <= n; l++) {
    for (int i = 1; i <= n - l + 1; i++) {
      int min_cost = std::numeric_limits<int>::max();
      for (int pivot = i + (l - 1) / 2; pivot < i + l - 1; pivot++) {
        int temp = pivot + std::max(dp[i][pivot - 1], dp[pivot + 1][i + l - 1]);
        min_cost = std::min(temp, min_cost);
      }
      dp[i][i + l - 1] = min_cost;
    }
  }
  return dp[1][n];
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
  std::cout << GetMinCost(n, dp) << std::endl;
  return 0;
}