/*
Time limit	2.5 seconds
Memory limit	256.0 MB
Input	stdin or input.txt
Output	stdout or output.txt

problem :
Rick sends Morty on a trip through N universes. He has a list of all existing unidirectional teleporters. 
To make sure Morty doesn't get lost, Rick needs to find out which universes have paths between them and which ones don't. Help him do it!!!

Input format
The first line contains the number of universes N (1 ≤ N ≤ 1 000). 
The next N rows are of length N, consist of zeros and ones and define the adjacency matrix of universes. 
A unit in the i-th row of the j-th column denotes a teleport from the i-th universe to the j-th universe.

Output format
Output a matrix where one in the i-th row of the j-th column denotes the existence of a path from the i-th universe to the j-th universe and zero denotes its absence.

Sample:
Input:
3
010
001
000
Output:
011
001
000

Notes:
A graph without loops.
*/

#include <iostream>
#include <vector>

std::vector<std::vector<bool>> MatrixMultiplication(
    std::vector<std::vector<bool>> m_1, std::vector<std::vector<bool>> m_2) {
  int n = static_cast<int>(m_1.size());
  std::vector<std::vector<bool>> res(n, std::vector<bool>(n, false));
  for (int i = 0; i < n; i++) {
    bool entry = false;
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n && !entry; k++) {
        entry = (m_1[i][k] && m_2[k][j]);
      }
      res[i][j] = entry;
    }
  }
  return res;
}

std::vector<std::vector<bool>> MatrixAddition(
    std::vector<std::vector<bool>> m_1, std::vector<std::vector<bool>> m_2) {
  int n = static_cast<int>(m_1.size());
  std::vector<std::vector<bool>> res(n, std::vector<bool>(n, false));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res[i][j] = (m_1[i][j] || m_2[i][j]);
    }
  }
  return res;
}

std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>>
PowerMatrix(std::vector<std::vector<bool>>& adj_matrix, int n) {
  if (n == 1) {
    return std::make_pair(adj_matrix, adj_matrix);
  }
  if (n == 2) {
    return std::make_pair(
        MatrixMultiplication(adj_matrix, adj_matrix),
        MatrixAddition(MatrixMultiplication(adj_matrix, adj_matrix),
                       adj_matrix));
  }
  if (n % 2 == 0) {
    std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>>
        matrix_pair = PowerMatrix(adj_matrix, n / 2);
    return std::make_pair(
        MatrixMultiplication(adj_matrix, matrix_pair.first),
        MatrixAddition(
            MatrixMultiplication(matrix_pair.first, matrix_pair.first),
            matrix_pair.second));
  }
  std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>>
      matrix_pair = PowerMatrix(adj_matrix, n - 1);
  return std::make_pair(
      MatrixMultiplication(adj_matrix, matrix_pair.first),
      MatrixAddition(MatrixMultiplication(matrix_pair.first, adj_matrix),
                     matrix_pair.second));
}

std::vector<std::vector<bool>> GetPaths(
    std::vector<std::vector<bool>>& adj_matrix, int n) {
  std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>>
      res = PowerMatrix(adj_matrix, n - 1);
  return res.second;
}

void Print(std::vector<std::vector<bool>>& paths) {
  for (unsigned long i = 0; i < paths.size(); i++) {
    for (unsigned long j = 0; j < paths.size(); j++) {
      std::cout << paths[i][j];
    }
    std::cout << std::endl;
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<bool>> adj_matrix(n, std::vector<bool>(n, false));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      std::cin >> c;
      if (c == '1') {
        adj_matrix[i][j] = true;
      }
    }
  }
  if (n == 1) {
    Print(adj_matrix);
    return 0;
  }
  std::vector<std::vector<bool>> paths = GetPaths(adj_matrix, n);
  Print(paths);
  return 0;
}
