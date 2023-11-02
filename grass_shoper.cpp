#include <iostream>

uint64_t T[5] = {8, 4, 2, 1, 1};
uint64_t F[5][5] = {{1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0},
                    {0, 0, 1, 0, 0},
                    {0, 0, 0, 1, 0}};
uint64_t M[5][5] = {{1, 1, 1, 1, 1},
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

void MultiplyMatrix(uint64_t M_1[5][5], uint64_t M_2[5][5]) {
  uint64_t temp[5][5] = {{1, 1, 1, 1, 1},
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
      uint64_t sum = 0;
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

uint64_t LastMultiplication(uint64_t M_3[5][5], uint64_t T[5]) {
  uint64_t t[5] = {0, 0, 0, 0, 0};
  for (int i = 0; i < 5; i++) {
    uint64_t sum = 0;
    for (int k = 0; k < 5; k++) {
      sum = (sum + ((M_3[i][k] % 1000003) * (T[k] % 1000003))) % 1000003;
    }
    t[i] = sum;
  }
  return t[0];
}

void PowerMatrix(uint64_t F[5][5], uint64_t n) {
  if (n == 0 || n == 1) {
    return;
  }
  PowerMatrix(F, n / 2);
  MultiplyMatrix(F, F);
  if (n % 2 != 0) {
    MultiplyMatrix(F, M);
  }
}

uint64_t CountSteps(uint64_t n) {
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
  uint64_t n;
  std::cin >> n;
  std::cout << CountSteps(n) << std::endl;
  return 0;
}
