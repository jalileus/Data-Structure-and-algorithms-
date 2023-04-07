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
