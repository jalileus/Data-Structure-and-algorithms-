#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int k_min = std::numeric_limits<int>::min();

class SegmentTree {
 public:
  SegmentTree(const std::vector<int>& arr, int n);
  ~SegmentTree();
  void BuildTree(int node, int start, int end);
  void UpdateRangeMax(int node, int start, int end, std::pair<int, int> segment,
                      int value);
  int GetMax(int node, int start, int end, int left, int right);

 private:
  std::vector<int> tree_;
  std::vector<int> accupation_;
  int size_;
};

SegmentTree::SegmentTree(const std::vector<int>& arr, int n)
    : accupation_(arr), size_(n) {
  tree_.resize(n * 4);
  BuildTree(0, 0, n - 1);
}

SegmentTree::~SegmentTree() {}

void SegmentTree::BuildTree(int node, int start, int end) {
  if (start == end) {
    tree_[node] = accupation_[end];
    return;
  }
  int mid = (start + end) / 2;
  BuildTree((node * 2) + 1, start, mid);
  BuildTree((node * 2) + 2, mid + 1, end);
  tree_[node] = std::max(tree_[(node * 2) + 1], tree_[(node * 2) + 2]);
}

void SegmentTree::UpdateRangeMax(int node, int start, int end,
                                 std::pair<int, int> segment, int value) {
  int l = segment.first;
  int r = segment.second;
  if (start > r || end < l) {
    return;
  }
  if (start == end) {
    tree_[node] += value;
    return;
  }
  int mid = (start + end) / 2;
  UpdateRangeMax((node * 2) + 1, start, mid, segment, value);
  UpdateRangeMax((node * 2) + 2, mid + 1, end, segment, value);
  tree_[node] = std::max(tree_[(node * 2) + 1], tree_[(node * 2) + 2]);
}

int SegmentTree::GetMax(int node, int start, int end, int left, int right) {
  if (start > right || end < left) {
    return k_min;
  }
  if (start >= left && end <= right) {
    return tree_[node];
  }
  int mid = (start + end) / 2;
  int left_max = GetMax((node * 2) + 1, start, mid, left, right);
  int right_max = GetMax((node * 2) + 2, mid + 1, end, left, right);
  return std::max(left_max, right_max);
}

int main() {
  int iglos_number, lodge_capacity, attempts_number;
  std::cin >> iglos_number;
  std::vector<int> initial_accupation(iglos_number);
  for (int i = 0; i < iglos_number; i++) {
    std::cin >> initial_accupation[i];
  }
  SegmentTree my_tree(initial_accupation, iglos_number);
  std::cin >> lodge_capacity >> attempts_number;
  std::vector<int> unsuccessful_attempts;

  for (int i = 0; i < attempts_number; i++) {
    int left, right, gunters;
    std::cin >> left >> right >> gunters;
    int new_accupation = my_tree.GetMax(0, 0, iglos_number - 1, left, right);
    if (new_accupation + gunters <= lodge_capacity) {
      my_tree.UpdateRangeMax(0, 0, iglos_number - 1,
                             std::make_pair(left, right), gunters);
    } else {
      unsuccessful_attempts.push_back(i);
    }
  }
  for (unsigned int i = 0; i < unsuccessful_attempts.size(); i++) {
    std::cout << unsuccessful_attempts[i] << " ";
  }
  return 0;
}