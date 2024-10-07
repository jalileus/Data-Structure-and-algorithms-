/*
Time limit	2 seconds
Memory limit	256Mb
Input	standard input or input.txt
Output	standard output or output.txt
problem :
An array of non-negative 64-bit integers is given. The number of numbers is at most 106. Sort the array using LSD byte-by-byte sorting.

Input format
The first line enters the number of numbers in the array N. Then go on N lines of N numbers.

Output format
Output this array, sorted in non-decreasing order.

Sample 1
Input	        Output
3               4
4               7
1000000        1000000
7

Sample 2
Input	
5
9244894871689
9521193378807
1748929606960
1006499032553
3289527480072
Output
1006499032553
1748929606960
3289527480072
9244894871689
9521193378807

Notes
It is forbidden to include algorithm!
*/

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
