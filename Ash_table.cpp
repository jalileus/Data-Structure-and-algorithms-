#include <iostream>
#include <vector>

class AshTable {
 public:
  AshTable();
  ~AshTable();
  void AddValue(int key);
  void RemoveValue(int key);
  bool FindValue(int key);

 private:
  int capacity_;
  int size_;
  std::vector<std::vector<int>> table_;
};

AshTable::AshTable() {
  size_ = 0;
  capacity_ = 256;
  table_.resize(capacity_);
}

AshTable::~AshTable() {}

void AshTable::AddValue(int key) {
  int new_index = key % capacity_;
  for (unsigned long int i = 0; i < table_[new_index].size(); i++) {
    if (table_[new_index][i] == key) {
      return;
    }
  }
  table_[new_index].push_back(key);
  size_++;
}

bool AshTable::FindValue(int key) {
  int new_index = key % capacity_;
  for (unsigned long int i = 0; i < table_[new_index].size(); i++) {
    if (table_[new_index][i] == key) {
      return true;
    }
  }
  return false;
}

void AshTable::RemoveValue(int key) {
  int new_index = key % capacity_;
  for (unsigned long int i = 0; i < table_[new_index].size(); i++) {
    if (table_[new_index][i] == key) {
      table_[new_index].erase(table_[new_index].begin() + i);
      size_--;
      return;
    }
  }
}

int main() {
  AshTable my_table;
  char input;
  int n;
  int value;
  std::cin >> n;
  while (n != 0) {
    std::cin >> input >> value;
    if (input == '+') {
      my_table.AddValue(value);
    } else if (input == '-') {
      my_table.RemoveValue(value);
    } else if (input == '?') {
      if (my_table.FindValue(value)) {
        std::cout << "YES" << std::endl;
      } else {
        std::cout << "NO" << std::endl;
      }
    }
    n--;
  }
  return 0;
}
