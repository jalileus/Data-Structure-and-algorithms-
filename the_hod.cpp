
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

int GetIndex(std::vector<std::vector<int>>& scc, int v) {
  for (unsigned long i = 0; i < scc.size(); i++) {
    if (std::find(scc[i].begin(), scc[i].end(), v) != scc[i].end()) {
      return i;
    }
  }
  return 0;
}

void Dfs(int source, std::vector<bool>& visited, std::stack<int>& order,
         std::vector<int>& component, std::vector<std::vector<int>>& graph) {
  visited[source] = true;
  component.push_back(source);
  for (int child : graph[source]) {
    if (!visited[child]) {
      Dfs(child, visited, order, component, graph);
    }
  }
  order.push(source);
}

class Graph {
 public:
  Graph(int n);
  ~Graph();
  void AddEdge(int from, int to);
  std::pair<int, int> GetDegree();
  Graph CreateGraph(std::vector<std::vector<int>>& scc);
  std::vector<std::vector<int>> Kosaraju();

 private:
  int v_;
  std::vector<std::vector<int>> adj_, rev_adj_;
};

Graph::Graph(int n) : v_(n), adj_(n), rev_adj_(n) {}

Graph::~Graph() {}

void Graph::AddEdge(int from, int to) {
  adj_[from].push_back(to);
  rev_adj_[to].push_back(from);
}

std::pair<int, int> Graph::GetDegree() {
  std::vector<int> in_degree(v_, 0), out_degree(v_, 0);
  for (int i = 0; i < v_; i++) {
    for (int j : adj_[i]) {
      out_degree[i]++;
      in_degree[j]++;
    }
  }
  int in_degrees = std::count(in_degree.begin(), in_degree.end(), 0);
  int out_degrees = std::count(out_degree.begin(), out_degree.end(), 0);

  return {in_degrees, out_degrees};
}

Graph Graph::CreateGraph(std::vector<std::vector<int>>& scc) {
  int new_size = scc.size();
  Graph new_graph(new_size);
  for (auto component : scc) {
    for (auto from : component) {
      for (auto to : adj_[from]) {
        int comp_index = GetIndex(scc, from);
        int comp_neibor_index = GetIndex(scc, to);
        if (comp_index != comp_neibor_index) {
          new_graph.AddEdge(comp_index, comp_neibor_index);
        }
      }
    }
  }
  return new_graph;
}

std::vector<std::vector<int>> Graph::Kosaraju() {
  std::vector<bool> visited(v_, false);
  std::vector<int> temp;
  std::stack<int> order;
  for (int i = 1; i < v_; ++i) {
    if (!visited[i]) {
      Dfs(i, visited, order, temp, adj_);
    }
  }
  temp.resize(0);
  visited.assign(v_, false);
  std::vector<std::vector<int>> scc;
  while (!order.empty()) {
    int source = order.top();
    order.pop();
    if (!visited[source]) {
      std::vector<int> component;
      Dfs(source, visited, order, component, rev_adj_);
      scc.push_back(component);
    }
  }
  return scc;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph my_graph(n + 1);
  for (int i = 0; i < m; i++) {
    int from, to;
    std::cin >> from >> to;
    my_graph.AddEdge(from, to);
  }
  std::vector<std::vector<int>> road = my_graph.Kosaraju();
  if (road.empty() || road.size() == 1 || m == 0) {
    std::cout << 0 << std::endl;
    return 0;
  }
  Graph new_road = my_graph.CreateGraph(road);
  std::pair<int, int> max_degree = new_road.GetDegree();
  int min_road = std::max(max_degree.first, max_degree.second);
  std::cout << min_road << std::endl;
  return 0;
}
