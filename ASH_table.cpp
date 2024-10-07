/*
Time limit	4 seconds
Memory limit	256Mb
Input	standard input or input.txt
Output	standard output or output.txt

problem :
We need to implement a data structure of a set that can quickly perform the following operations:

«+ N» — add a number N to the set. It is not guaranteed that N is not in the set.
«- N» — remove number N from the set. It is not guaranteed that N is present in the set.
«? N» — find out if N is in the set.

Output format
For each query of type 3, print YES if the answer is positive, and NO — otherwise.

Sample 1:
input:
10
+ 0
+ 1
+ 2
? 2
+ 2
? 2
- 2
? 2
- 0
? 0
output:
YES
YES
NO
NO

Sample 2:
input:
10
+ 2
+ 0
? 1
- 2
? 2
? 2
+ 1
+ 1
? 0
- 0
output:
NO
NO
NO
YES
*/

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
