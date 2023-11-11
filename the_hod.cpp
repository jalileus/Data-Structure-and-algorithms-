
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

struct NewGraph {
  int size;
  std::vector<std::vector<int>> new_adj, new_rev_adj;
  NewGraph(int n) : size(n), new_adj(n), new_rev_adj(n) {}
  void AddEdge(int v, int w) {
    new_adj[v].push_back(w);
    new_rev_adj[w].push_back(v);
  }
};

class Graph {
 public:
  friend NewGraph;
  Graph(int n, std::vector<std::vector<int>>& graph,
        std::vector<std::vector<int>>& graph_reversed);
  ~Graph();
  void AddEdge(int from, int to);
  void FirstDFs(int source, std::vector<bool>& visited, std::stack<int>& order);
  void SecondDfs(int source, std::vector<bool>& visited,
                 std::vector<int>& component);
  std::vector<std::vector<int>> Kosaraju();
  std::pair<int, int> GetDegree(std::vector<std::vector<int>>& new_graph,
                                int new_size);
  NewGraph CreateGraph(std::vector<std::vector<int>>& scc);
  int GetMinRoads();
  int GetIndex(std::vector<std::vector<int>>& scc, int v);

 private:
  int v_;
  std::vector<std::vector<int>> adj_, rev_adj_;
};

Graph::Graph(int n, std::vector<std::vector<int>>& graph,
             std::vector<std::vector<int>>& graph_reversed)
    : v_(n), adj_(graph), rev_adj_(graph_reversed) {}

Graph::~Graph() {}

void Graph::AddEdge(int from, int to) {
  adj_[from].push_back(to);
  rev_adj_[to].push_back(from);
}

void Graph::FirstDFs(int source, std::vector<bool>& visited,
                     std::stack<int>& order) {
  visited[source] = true;
  for (int child : adj_[source]) {
    if (!visited[child]) {
      FirstDFs(child, visited, order);
    }
  }
  order.push(source);
}

void Graph::SecondDfs(int source, std::vector<bool>& visited,
                      std::vector<int>& component) {
  visited[source] = true;
  component.push_back(source);
  for (int child : rev_adj_[source]) {
    if (!visited[child]) {
      SecondDfs(child, visited, component);
    }
  }
}

std::vector<std::vector<int>> Graph::Kosaraju() {
  std::vector<bool> visited(v_, false);
  std::stack<int> order;
  for (int i = 1; i < v_; ++i) {
    if (!visited[i]) {
      FirstDFs(i, visited, order);
    }
  }
  visited.assign(v_, false);
  std::vector<std::vector<int>> scc;
  while (!order.empty()) {
    int source = order.top();
    order.pop();
    if (!visited[source]) {
      std::vector<int> component;
      SecondDfs(source, visited, component);
      scc.push_back(component);
    }
  }
  return scc;
}

int Graph::GetIndex(std::vector<std::vector<int>>& scc, int v) {
  for (unsigned long i = 0; i < scc.size(); i++) {
    if (std::find(scc[i].begin(), scc[i].end(), v) != scc[i].end()) {
      return i;
    }
  }
  return 0;
}

NewGraph Graph::CreateGraph(std::vector<std::vector<int>>& scc) {
  int new_size = scc.size();
  NewGraph new_graph(new_size);
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

std::pair<int, int> Graph::GetDegree(std::vector<std::vector<int>>& new_graph,
                                     int new_size) {
  std::vector<int> in_degree(new_size, 0), out_degree(new_size, 0);
  for (int i = 0; i < new_size; i++) {
    for (int j : new_graph[i]) {
      out_degree[i]++;
      in_degree[j]++;
    }
  }
  int in_degrees = std::count(in_degree.begin(), in_degree.end(), 0);
  int out_degrees = std::count(out_degree.begin(), out_degree.end(), 0);

  return {in_degrees, out_degrees};
}

int Graph::GetMinRoads() {
  std::vector<std::vector<int>> road = Kosaraju();
  if (road.empty()) {
    return 0;
  }
  if (road.size() == 1) {
    return 0;
  }
  NewGraph new_road = CreateGraph(road);
  int size = new_road.new_adj.size();
  std::pair<int, int> max_degree = GetDegree(new_road.new_adj, size);
  int min_road = std::max(max_degree.first, max_degree.second);
  return min_road;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n + 1), graph_reversed(n + 1);
  Graph my_graph(n + 1, graph, graph_reversed);
  for (int i = 0; i < m; i++) {
    int from, to;
    std::cin >> from >> to;
    my_graph.AddEdge(from, to);
  }
  if (m == 0) {
    std::cout << 0 << std::endl;
  } else {
    std::cout << my_graph.GetMinRoads() << std::endl;
  }
  return 0;
}
