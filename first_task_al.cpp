#include <iostream>

int main() {
  unsigned long long int Number_;
  unsigned long long int rev = 0;

  std::cin >> Number_;

  for (; Number_ != 0;) {
    rev = (rev * 10) + (Number_ % 10);
    Number_ = Number_ / 10;
  }

  std::cout << rev;

  return 0;
}
