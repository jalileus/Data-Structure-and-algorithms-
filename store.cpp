#include <iostream>
#include <list>
#include <vector>

class Graph {
 public:
  Graph(int v);
  ~Graph();
  void AddEdge(int v, int w);
  std::vector<int> Bfs(int source);

 private:
  int v_;
  std::list<int>* adj_;
};

Graph::Graph(int v) : v_(v) { adj_ = new std::list<int>[v_ + 1]; }

Graph::~Graph() { delete[] adj_; }

void Graph::AddEdge(int v, int w) {
  adj_[v].push_back(w);
  adj_[w].push_back(v);
}

std::vector<int> Graph::Bfs(int source) {
  std::vector<int> short_path(v_ + 1, 0);
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
        short_path[*child] = short_path[end_path] + 1;
        queue.push_back(*child);
      }
    }
  }
  return short_path;
}

int GetShortestPath(int vertices, std::vector<std::vector<int>>& path) {
  int base_case = 2 * vertices;
  for (int i = 1; i <= vertices; i++) {
    int shortest_path = path[0][i] + path[1][i] + path[2][i];
    if (shortest_path < base_case) {
      base_case = shortest_path;
    }
  }
  return base_case;
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
  std::vector<std::vector<int>> path(3);
  path[0] = my_graph.Bfs(s);
  path[1] = my_graph.Bfs(w);
  path[2] = my_graph.Bfs(v);
  std::cout << GetShortestPath(n, path) << std::endl;
  return 0;
}
