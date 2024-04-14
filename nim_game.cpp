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

int CalculateGrundy(int heap_size, std::vector<int> removals) {
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

int main() {
  int k, q;

  std::cin >> k;

  std::vector<int> removals(k);

  for (int i = 0; i < k; i++) {
    std::cin >> removals[i];
  }

  std::cin >> q;

  std::vector<int> res(q);

  for (int i = 0; i < q; i++) {
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
  for (unsigned int i = 0; i < res.size(); i++) {
    if (res[i] == 0) {
      std::cout << "L";
    } else {
      std::cout << "W";
    }
  }
  return 0;
}