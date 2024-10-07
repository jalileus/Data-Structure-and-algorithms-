/*

time limit : 3 seconds
memory limit : 256 MB

problem :
In this problem you need to write a function with a given prototype:
bool BinarySearch(const int* begin, const int* end, int target);
It returns true if half-interval [begin, end) has value target.

input format:
The first line contains the number N (1 ≤ N ≤ 105) — the length of the array. The second line contains N integers in non-decreasing order. It is guaranteed that they do not exceed 109 in modulo.
The third line contains a single number Q (1 ≤ Q ≤ 105) —the number of times BinarySearch is called.
Then comes Q lines of queries in the format «i j t» (0 ≤ i < j ≤ N, |t| ≤ 109): i, j — indexes of array, setting half-interval for function call, t — argument target in function call.

output format:
For each function call, print YES if it returned true, and NO — otherwise.

sample
input	          output 
5                 NO
1 2 3 4 5         YES
5                 NO
0 3 4             YES
0 3 3             YES
1 5 6
1 2 2
0 5 5

*/

#include <iostream>

bool BinarySearch(const int *begin, const int *end, int target) {
  const int *middle;

  if (end >= begin) {
    middle = begin + (end - begin) / 2;

    if (*middle == target)
      return true;

    if (*middle > target)
      return BinarySearch(begin, middle - 1, target);
    else
      return BinarySearch(middle + 1, end, target);
  }
  return false;
}

int main() {
  int size, begin, end, target, frequency;

  std::cin >> size;

  int *array = new int[size];

  for (int counter = 0; counter < size; counter++) {
    std::cin >> array[counter];
  }

  std::cin >> frequency;

  while (frequency != 0) {

    std::cin >> begin >> end >> target;

    if (BinarySearch(&array[begin], &array[end - 1], target)) {
      std::cout << "YES" << std::endl;
    } else
      std::cout << "NO" << std::endl;

    frequency = frequency - 1;
  }

  delete[] array;

  return 0;
}
