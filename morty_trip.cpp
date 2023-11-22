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
