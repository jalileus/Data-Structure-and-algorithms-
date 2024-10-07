#include <iostream>

int main() {
  unsigned long long int number;
  unsigned long long int reverse = 0;

  std::cin >> number;

  for (; number != 0;) {
    reverse = (reverse * 10) + (number % 10);
    number = number / 10;
  }

  std::cout << reverse;

  return 0;
}
