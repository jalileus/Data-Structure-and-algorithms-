#include <iostream>

class Fibonacci {
 public:
  Fibonacci(unsigned long long n);
  ~Fibonacci();
  unsigned long long Fib(unsigned long long n);
  void Matrix_Power(unsigned long long F[2][2], unsigned long long n);
  void Matrix_Multiplication(unsigned long long M[2][2],
                             unsigned long long F[2][2]);
  unsigned long long F[2][2] = {{1, 1}, {1, 0}};
  unsigned long long M[2][2] = {{1, 1}, {1, 0}};

 private:
  unsigned long long n;
};

Fibonacci::Fibonacci(unsigned long long n) { n = 0; }

Fibonacci::~Fibonacci() {}

void Fibonacci::Matrix_Power(unsigned long long F[2][2], unsigned long long n) {
  if (n == 0 || n == 1) {
    return;
  }
  Matrix_Power(F, n / 2);
  unsigned long long a = F[0][0] * F[0][0] + F[0][1] * F[1][0];
  unsigned long long b = F[0][0] * F[0][1] + F[0][1] * F[1][1];
  unsigned long long c = F[1][0] * F[0][0] + F[1][1] * F[1][0];
  unsigned long long d = F[1][0] * F[0][1] + F[1][1] * F[1][1];

  F[0][0] = a % 1000003;
  F[0][1] = b % 1000003;
  F[1][0] = c % 1000003;
  F[1][1] = d % 1000003;

  if (n % 2 != 0) {
    unsigned long long a = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    unsigned long long b = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    unsigned long long c = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    unsigned long long d = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = a % 1000003;
    F[0][1] = b % 1000003;
    F[1][0] = c % 1000003;
    F[1][1] = d % 1000003;
  }
}

unsigned long long Fibonacci::Fib(unsigned long long n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  }
  Matrix_Power(F, n - 1);
  return F[0][0];
}

int main() {
  unsigned long long n;
  std::cin >> n;
  Fibonacci fib(n);
  std::cout << fib.Fib(n - 1) << std::endl;
  return 0;
}
