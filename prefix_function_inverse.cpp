#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string PrefixToString(const std::vector<int>& prefix, std::string& res) {
  std::vector<char> missmatch(prefix.size(), 'b');
  res[0] = 'a';
  for (unsigned i = 1; i < prefix.size(); i++) {
    if (prefix[i] == 0) {
      res[i] = missmatch[i - 1];
      missmatch[i] = 'b';

    } else {
      res[i] = res[prefix[i] - 1];
      missmatch[i] =
          std::max(missmatch[prefix[i] - 1], (char)(res[prefix[i]] + 1));
    }
  }
  return res;
}

std::vector<int> InitializeVector(const std::string& values) {
  std::vector<int> prefix_func;
  std::stringstream c(values);
  int num;
  while (c >> num) {
    prefix_func.push_back(num);
  }
  return prefix_func;
}

std::string DoTransform(const std::vector<int>& prefix_func) {
  char start_char = 'a';
  std::string start_string(prefix_func.size(), start_char);
  std::string res = PrefixToString(prefix_func, start_string);
  return res;
}

int main() {
  std::string values;
  std::getline(std::cin, values);
  std::vector<int> prefix_func = InitializeVector(values);
  std::string res = DoTransform(prefix_func);
  std::cout << res << std::endl;
  return 0;
}