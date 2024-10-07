/*
Time limit	1 second
Memory limit	256Mb
Input	standard input or input.txt
Output	standard output or output.txt

problem : 
In this problem you need to find the k-order statistic (k-order by non-decreasing) of the numerical sequence A, the elements of which are given as follows:
A[i] = (A[i-1] * 123 + A[I-2] * 45) % (10^7 + 4321)

Input format
You are given n, k, A0, A1(1 ≤ k ≤ n ≤ 107, 0 ≤ Ai < 107 + 4321) —the number of numbers in the number sequence, k from the condition and the first two numbers of the number sequence.

Output format
Output k-order statistic.

Sample 1
Input	          Output
2 2 100 1000     1000

Sample 2
Input	          Output
10 5 1 2        321287

Notes :
To get double the score for the problem, you need to write an algorithm that guarantees finding the kth ordinal for O(n) in the worst case.
*/

#include <algorithm>
#include <iostream>

void CreatArray(int* arr, int first, int second, int n) {
  arr[0] = first;
  arr[1] = second;
  for (int i = 2; i < n; i++) {
    arr[i] = (arr[i - 1] * 123 + arr[i - 2] * 45) % (10000000 + 4321);
  }
}

void InsertionSort(int* arr, int start, int end) {
  for (int i = start + 1; i <= end; i++) {
    int key = arr[i];
    int j = i - 1;
    while (j >= start && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

int FindIndex(int* arr, int start, int end, int k) {
  int left = start;
  int right = end;
  while (left <= right) {
    if (arr[left] == k) {
      return left;
    }
    if (arr[right] == k) {
      return right;
    }
    left++;
    right--;
  }
  return -1;
}

int MedianOfMedians(int* arr, int start, int end) {
  int size = end - start + 1;
  if (size <= 5) {
    InsertionSort(arr, start, end);
    return arr[start + size / 2];
  }
  int number_of_groups = size / 5 + (size % 5 == 0 ? 0 : 1);
  int* medians = new int[number_of_groups];
  for (int i = 0; i < number_of_groups; i++) {
    int group_start = start + (i * 5);
    int group_end = std::min(group_start + 4, end);
    medians[i] = MedianOfMedians(arr, group_start, group_end);
  }
  int median_of_medians = MedianOfMedians(medians, 0, number_of_groups - 1);
  delete[] medians;
  return median_of_medians;
}

int Partition(int* arr, int start, int end, int pivot) {
  int index_pivot = FindIndex(arr, start, end, pivot);
  pivot = arr[index_pivot];
  std::swap(arr[index_pivot], arr[end]);
  int i = start - 1;
  for (int j = start; j < end; j++) {
    if (arr[j] <= pivot) {
      i++;
      std::swap(arr[j], arr[i]);
    }
  }
  std::swap(arr[i + 1], arr[end]);
  return i + 1;
}

int FindKthorder(int* arr, int start, int end, int k) {
  if (start == end) {
    return arr[start];
  }
  int median_of_medians = MedianOfMedians(arr, start, end);
  int index_pivot = Partition(arr, start, end, median_of_medians);
  int rank_pivot = index_pivot - start + 1;
  if (k == rank_pivot) {
    return arr[index_pivot];
  } else if (k < rank_pivot) {
    return FindKthorder(arr, start, index_pivot - 1, k);
  } else {
    return FindKthorder(arr, index_pivot + 1, end, k - rank_pivot);
  }
}

int main() {
  int size, kth_element, first_element, second_element;
  std::cin >> size >> kth_element >> first_element >> second_element;
  int* array = new int[size];
  CreatArray(array, first_element, second_element, size);
  std::cout << FindKthorder(array, 0, size - 1, kth_element) << std::endl;
  delete[] array;
  return 0;
}
