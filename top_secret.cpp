#include <iostream>
#include <list>
#include <stack>
#include <vector>

class Graph {
 public:
  Graph(int n);
  ~Graph();
  bool TopSort();
  void AddEdge(int parent, int child);
  std::vector<int> vec_order;

 private:
  int v_;
  std::vector<int> neighbors_;
  std::list<int>* adj_;
};

Graph::Graph(int n) : v_(n) {
  adj_ = new std::list<int>[n];
  neighbors_.resize(n, 0);
}

Graph::~Graph() { delete[] adj_; }

void Graph::AddEdge(int parent, int child) {
  adj_[parent].push_back(child);
  neighbors_[child]++;
}

bool Graph::TopSort() {
  unsigned long number_of_vertices = v_;
  std::stack<int> count_neighbors;
  for (int i = 0; i < v_; i++) {
    if (neighbors_[i] == 0) {
      count_neighbors.push(i);
    }
  }
  while (!count_neighbors.empty()) {
    int start = count_neighbors.top();
    vec_order.push_back(start);
    count_neighbors.pop();
    for (auto child = adj_[start].begin(); child != adj_[start].end();
         child++) {
      if (--neighbors_[*child] == 0) {
        count_neighbors.push(*child);
      }
    }
  }
  return (number_of_vertices == vec_order.size());
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph my_graph(n);
  for (int i = 0; i < m; i++) {
    int parent, child;
    std::cin >> parent >> child;
    my_graph.AddEdge(parent, child);
  }
  if (my_graph.TopSort()) {
    std::cout << "YES" << std::endl;
    for (unsigned long i = 0; i < my_graph.vec_order.size(); i++) {
      std::cout << my_graph.vec_order[i] << " ";
    }
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}