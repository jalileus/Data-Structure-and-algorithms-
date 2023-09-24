#include <iostream>

unsigned long long T[5] = {8, 4, 2, 1, 1};
unsigned long long F[5][5] = {{1, 1, 1, 1, 1},
                              {1, 0, 0, 0, 0},
                              {0, 1, 0, 0, 0},
                              {0, 0, 1, 0, 0},
                              {0, 0, 0, 1, 0}};
unsigned long long M[5][5] = {{1, 1, 1, 1, 1},
                              {
                                  1,
                                  0,
                                  0,
                                  0,
                                  0,
                              },
                              {0, 1, 0, 0, 0},
                              {0, 0, 1, 0, 0},
                              {0, 0, 0, 1, 0}};

void MultiplyMatrix(unsigned long long M_1[5][5],
                    unsigned long long M_2[5][5]) {
  unsigned long long temp[5][5] = {{1, 1, 1, 1, 1},
                                   {
                                       1,
                                       0,
                                       0,
                                       0,
                                       0,
                                   },
                                   {0, 1, 0, 0, 0},
                                   {0, 0, 1, 0, 0},
                                   {0, 0, 0, 1, 0}};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      unsigned long long sum = 0;
      for (int k = 0; k < 5; k++) {
        sum = (sum + ((M_1[i][k] % 1000003) * (M_2[k][j] % 1000003))) % 1000003;
      }
      temp[i][j] = sum;
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      M_1[i][j] = temp[i][j];
    }
  }
}

unsigned long long LastMultiplication(unsigned long long M_3[5][5],
                                      unsigned long long T[5]) {
  unsigned long long t[5] = {0, 0, 0, 0, 0};
  for (int i = 0; i < 5; i++) {
    unsigned long long sum = 0;
    for (int k = 0; k < 5; k++) {
      sum = (sum + ((M_3[i][k] % 1000003) * (T[k] % 1000003))) % 1000003;
    }
    t[i] = sum;
  }
  return t[0];
}

void PowerMatrix(unsigned long long F[5][5], unsigned long long n) {
  if (n == 0 || n == 1) {
    return;
  }
  PowerMatrix(F, n / 2);
  MultiplyMatrix(F, F);
  if (n % 2 != 0) {
    MultiplyMatrix(F, M);
  }
}

unsigned long long CountSteps(unsigned long long n) {
  if (n == 0) {
    return 0;
  } else if (n == 1 || n == 2) {
    return 1;
  } else if (n == 3) {
    return 2;
  } else if (n == 4) {
    return 4;
  } else if (n == 5) {
    return 8;
  }
  PowerMatrix(F, n - 5);
  return LastMultiplication(F, T);
}

int main() {
  unsigned long long n;
  std::cin >> n;
  std::cout << CountSteps(n) << std::endl;
  return 0;
}