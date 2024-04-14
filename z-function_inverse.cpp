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

int main() {
  std::vector<int> z_func;
  std::string values;
  std::getline(std::cin, values);
  std::stringstream c(values);
  int num;
  while (c >> num) {
    z_func.push_back(num);
  }
  char start_char = 'a';
  std::string start_string(z_func.size(), start_char);
  std::vector<int> prefix = GetPrefix(z_func);
  std::string res = PrefixToString(prefix, start_string);
  std::cout << res << std::endl;
  return 0;
}