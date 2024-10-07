/* 
Time limit	0.055 seconds
Memory limit	3.0 MB
Input	stdin or input.txt
Output	stdout or output.txt

problem : 
We already played Nim game as follows:

The starting position has some heaps, all containing a number of beads (not necessarily equal).

The players take turns chosing a heap and then remove a positive number of beads from it.

If the first player not able to make a move, loses.

But unfortunately, the game becomes boring since we know that we just need to Xor the number of beads
in the heaps in the current position and if the xor-sum is 0, you will lose. Luckily for you guys, we came up with a new version with an additional rule:

Each player is now only allowed to remove a number of beads in some predefined set S
It means that if we have S,S = {2,5} each player is only allowed to remove or 2 or 5 beads.

Your job is to write a program that determines if a position is a losing or a winning position.

Input format :
The first line contains a number k - the size of S (1 <= k <= 100) followed by k numbers xi (1 <= xi <= 10000) describing S. The second line is q - the number of positions to calculate the result. 
The next q lines each contain a number j (1 <= j <= 100) describing the number of heaps and j numbers yi (0 <= yi <= 10000) describing the number of beads in the heaps.

Output format
If the position is a winning position, print "W" If it's losing position, print "L"

Sample
Input	       Output
2 2 5         LWW 
3
2 5 12
3 2 4 7
4 2 3 7 12

*/

#include <iostream>
#include <unordered_map>
#include <vector>

std::unordered_map<int, int> memo;

int CalculateMex(std::vector<int> set) {
  std::vector<bool> check_set(set.size() + 1, 0);
  for (int element : set) {
    check_set[element] = true;
  }
  int mex = 0;
  while (check_set[mex]) {
    mex++;
  }
  return mex;
}

int CalculateGrundy(int heap_size, const std::vector<int>& removals) {
  if (heap_size == 0) {
    return 0;
  }
  if (memo.find(heap_size) != memo.end()) {
    return memo[heap_size];
  }
  std::vector<int> next_position;
  for (int move : removals) {
    if (heap_size >= move) {
      next_position.push_back(CalculateGrundy(heap_size - move, removals));
    }
  }
  int grundy = CalculateMex(next_position);
  memo[heap_size] = grundy;
  return grundy;
}

std::vector<int> GetResult(const std::vector<int>& removals, int num_pos) {
  std::vector<int> res(num_pos);
  for (int i = 0; i < num_pos; i++) {
    int heaps_num;
    int total_grundy = 0;
    std::cin >> heaps_num;
    for (int j = 0; j < heaps_num; j++) {
      int heap_size;
      std::cin >> heap_size;
      total_grundy ^= CalculateGrundy(heap_size, removals);
    }
    res[i] = total_grundy;
  }
  return res;
}

int main() {
  int size_removals, num_pos;
  std::cin >> size_removals;
  std::vector<int> removals(size_removals);
  for (int i = 0; i < size_removals; i++) {
    std::cin >> removals[i];
  }
  std::cin >> num_pos;
  std::vector<int> res = GetResult(removals, num_pos);
  for (unsigned i = 0; i < res.size(); i++) {
    if (res[i] == 0) {
      std::cout << "L";
    } else {
      std::cout << "W";
    }
  }
  return 0;
}
