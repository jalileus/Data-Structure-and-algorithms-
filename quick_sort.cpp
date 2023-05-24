#include <algorithm>
#include <iostream>

long BinarySearch(long long* arr, long start, long end, long target) {
  while (start <= end) {
    long mid = start + (end - start) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }
  return start;
}

void InsertionSort(long long* arr, long start, long end) {
  for (long i = start + 1; i <= end; i++) {
    long position = BinarySearch(arr, start, i - 1, arr[i]);
    long long temp = arr[i];
    long j = i - 1;
    while (j >= position) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = temp;
  }
}

long long MedianOfMedians(long long* arr, long start, long end) {
  long size = end - start + 1;
  if (size <= 5) {
    InsertionSort(arr, start, end);
    return arr[start + size / 2];
  }
  long number_of_groups = size / 5 + (size % 5 == 0 ? 0 : 1);
  long long* medians = new long long[number_of_groups];
  for (long i = 0; i < number_of_groups; i++) {
    long group_start = start + (i * 5);
    long group_end = std::min(group_start + 4, end);
    medians[i] = MedianOfMedians(arr, group_start, group_end);
  }
  long long median_of_medians =
      MedianOfMedians(medians, 0, number_of_groups - 1);
  delete[] medians;
  return median_of_medians;
}

void QuickSort(long long* arr, long start, long end) {
  while (start < end) {
    if (end - start < 10) {
      InsertionSort(arr, start, end);
      break;
    }
    long long pivot = MedianOfMedians(arr, start, end);
    long i = start;
    long j = end;
    while (i <= j) {
      while (arr[i] < pivot) i++;
      while (arr[j] > pivot) j--;
      if (i <= j) {
        std::swap(arr[i], arr[j]);
        i++;
        j--;
      }
    }
    if (j - start < end - i) {
      QuickSort(arr, start, j);
      start = i;
    } else {
      QuickSort(arr, i, end);
      end = j;
    }
  }
}

void Sort(long long* arr, long start, long end, long size) {
  if (size < 256) {
    InsertionSort(arr, start, end);
    return;
  } else {
    QuickSort(arr, start, end);
    return;
  }
}

void PrintArray(long long* arr, long n) {
  for (long i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
}

int main() {
  long size;
  std::cin >> size;
  long long* array = new long long[size];
  for (long i = 0; i < size; i++) {
    std::cin >> array[i];
  }
  QuickSort(array, 0, size - 1);
  PrintArray(array, size);
  delete[] array;
  return 0;
}