#include <iostream>
#include <list>
#include <vector>

class Graph {
 public:
  Graph(int v);
  ~Graph();
  void AddEdge(int v, int w);
  void Bfs(std::vector<int>& shortest_path, int source);
  int GetShortestPath(int v, int w, int s);

 private:
  int v_;
  std::vector<int> shortest_path_1_;
  std::vector<int> shortest_path_2_;
  std::vector<int> shortest_path_3_;
  std::list<int>* adj_;
};

Graph::Graph(int v) : v_(v) {
  adj_ = new std::list<int>[v_ + 1];
  shortest_path_1_.resize(v_ + 1, 0);
  shortest_path_2_.resize(v_ + 1, 0);
  shortest_path_3_.resize(v_ + 1, 0);
}

Graph::~Graph() { delete[] adj_; }

void Graph::AddEdge(int v, int w) {
  adj_[v].push_back(w);
  adj_[w].push_back(v);
}

int Graph::GetShortestPath(int v, int w, int s) {
  Bfs(shortest_path_1_, s);
  Bfs(shortest_path_2_, v);
  Bfs(shortest_path_3_, w);
  int base_case = v_ * 2;
  for (int i = 1; i <= v_; i++) {
    int shortest_path =
        shortest_path_1_[i] + shortest_path_2_[i] + shortest_path_3_[i];
    if (shortest_path < base_case) {
      base_case = shortest_path;
    }
  }
  return base_case;
}

void Graph::Bfs(std::vector<int>& shortest_path, int source) {
  std::vector<bool> visited(v_ + 1, false);
  visited[source] = true;
  std::list<int> queue;
  queue.push_back(source);
  int end_path = source;
  while (!queue.empty()) {
    end_path = queue.front();
    queue.pop_front();
    for (auto child = adj_[end_path].begin(); child != adj_[end_path].end();
         child++) {
      if (!visited[*child]) {
        visited[*child] = true;
        shortest_path[*child] = shortest_path[end_path] + 1;
        queue.push_back(*child);
      }
    }
  }
}

int main() {
  int n, m, v, w, s;
  std::cin >> n >> m >> v >> w >> s;
  Graph my_graph(n);
  for (int i = 0; i < m; i++) {
    int parent, child;
    std::cin >> parent;
    std::cin >> child;
    my_graph.AddEdge(parent, child);
  }
  if ((v == w && w == s) || m == 0) {
    std::cout << 0;
    return 0;
  }
  std::cout << my_graph.GetShortestPath(v, w, s);
  return 0;
}