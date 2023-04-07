#include <iostream>

int main() {
  unsigned long long int Number;
  unsigned long long int Reverse = 0;

  std::cin >> Number;

  for (; Number != 0;) {
    Reverse = (Reverse * 10) + (Number % 10);
    Number = Number / 10;
  }

  std::cout << Reverse;

  return 0;
}
