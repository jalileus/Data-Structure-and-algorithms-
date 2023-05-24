#include <cmath>
#include <cstring>
#include <iostream>

int size_int = sizeof(int);
int max_bytes = sizeof(unsigned long long);

unsigned char GetByte(unsigned long long number, int i) {
  return (number >> (8 * i)) & 0xFF;
}

void SortByBytes(unsigned long long* arr, int n) {
  int pos[256] = {0};
  int count[256] = {0};
  unsigned long long* container = new unsigned long long[n];
  for (int byte_pos = 0; byte_pos < max_bytes; byte_pos++) {
    std::memset(count, 0, size_int * 256);
    std::memset(pos, 0, size_int * 256);
    for (int i = 0; i < n; i++) {
      unsigned char byte_value = GetByte(arr[i], byte_pos);
      count[byte_value]++;
    }
    pos[0] = 0;
    for (int i = 1; i < 256; i++) {
      pos[i] = pos[i - 1] + count[i - 1];
    }
    for (int i = 0; i < n; i++) {
      unsigned char byte_value = GetByte(arr[i], byte_pos);
      container[pos[byte_value]] = arr[i];
      pos[byte_value]++;
    }
    std::memcpy(arr, container, n * max_bytes);
  }
  delete[] container;
}

void Print(unsigned long long* arr, long n) {
  for (long i = 0; i < n; i++) {
    std::cout << arr[i] << '\n';
  }
}
int main() {
  int size;
  std::cin >> size;
  unsigned long long* array = new unsigned long long[size];
  for (int i = 0; i < size; i++) {
    std::cin >> array[i];
  }
  SortByBytes(array, size);
  Print(array, size);
  delete[] array;
  return 0;
}