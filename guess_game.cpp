/*
Time limit	0.008 seconds
Memory limit	9.5 MB
Input	stdin or input.txt
Output	stdout or output.txt

problem :
Yesterday, Doctor Strange came up with an interesting game about numbers and he really wants to play it with you.

Doctor Strange will choose a number between 1 and n, and you need to guess what it is. Of course, you don't have the ability that Doctor Strange does, so he will give you some useful hints.

If you guess it right, congratulation, you win the game.

If you guess the wrong number, don't worry, Doctor Strange will tell you whether the number you chose is bigger or smaller, and you can continue guessing.

BUT THERE IS A CATCH HERE.

Each incorrect guess of a number, represented as x, incurs a payment of x dollars. If your funds are depleted, you will face defeat in the game.

Your task is to write a program. Given n, return the minimum amount of money you need to guarantee a win regardless of what number Doctor Strange pick.

Good luck !

Input format
1 <= n <=200

Output format
Output the minimum amount of money you need to guarantee a win

Sample 1
Input	Output
  1     0
Sample 2
Input	Output
  2      1
1
*/

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
