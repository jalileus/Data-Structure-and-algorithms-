#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

std::size_t GetMinCost(std::size_t upper_bound,
                       std::vector<std::vector<std::size_t>> dp) {
  for (std::size_t l = 2; l <= upper_bound; l++) {
    for (std::size_t i = 1; i <= upper_bound - l + 1; i++) {
      std::size_t min_cost = std::numeric_limits<std::size_t>::max();
      for (std::size_t pivot = i + (l - 1) / 2; pivot < i + l - 1; pivot++) {
        std::size_t temp =
            pivot + std::max(dp[i][pivot - 1], dp[pivot + 1][i + l - 1]);
        min_cost = std::min(temp, min_cost);
      }
      dp[i][i + l - 1] = min_cost;
    }
  }
  return dp[1][upper_bound];
}

int main() {
  std::size_t upper_bound;
  std::cin >> upper_bound;
  std::vector<std::vector<std::size_t>> dp(
      upper_bound + 1, std::vector<std::size_t>(upper_bound + 1, 0));
  std::cout << GetMinCost(upper_bound, dp) << std::endl;
  return 0;
}
