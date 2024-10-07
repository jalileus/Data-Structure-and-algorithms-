/*
Time limit	1 second
Memory limit	12.0 MB
Input	stdin or input.txt
Output	stdout or output.txt

peoblem :
In this exercise, you need to find the string with the smallest lexicographical order constructed from the given Z-function in the alphabet a-z.

Sample
Input	         Output
5 3 2 1 0       aaaab

*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> GetPrefix(const std::vector<int>& z_func) {
  std::vector<int> prefix(z_func.size(), 0);
  int size_z_func = z_func.size();
  for (int i = 1; i < size_z_func; i++) {
    prefix[i + z_func[i] - 1] = std::max(prefix[i + z_func[i] - 1], z_func[i]);
  }
  for (int i = size_z_func - 2; i >= 0; i--) {
    prefix[i] = std::max(prefix[i + 1] - 1, prefix[i]);
  }
  return prefix;
}

std::string PrefixToString(const std::vector<int>& prefix, std::string& res) {
  for (unsigned i = 1; i < prefix.size(); i++) {
    if (prefix[i] == 0) {
      res[i] = res[prefix[i - 1]] + 1;
    } else {
      res[i] = res[prefix[i] - 1];
    }
  }
  return res;
}

std::vector<int> InitializeVector(const std::string& values) {
  std::vector<int> z_func_vector;
  std::stringstream c(values);
  int num;
  while (c >> num) {
    z_func_vector.push_back(num);
  }
  return z_func_vector;
}

std::string DoTransform(const std::vector<int>& z_func) {
  char start_char = 'a';
  std::string start_string(z_func.size(), start_char);
  std::vector<int> prefix = GetPrefix(z_func);
  std::string res = PrefixToString(prefix, start_string);
  return res;
}

int main() {
  std::string values;
  std::getline(std::cin, values);
  std::vector<int> z_func = InitializeVector(values);
  std::string res = DoTransform(z_func);
  std::cout << res << std::endl;
  return 0;
}
