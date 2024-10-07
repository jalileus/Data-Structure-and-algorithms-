/*
Time limit	3 seconds
Memory limit	256Mb
Input	standard input or input.txt
Output	standard output or output.txt

problem :
Frank again receives a new order. This time, however, 
the city plays by very strange rules: all roads in the city are one-way and connect only offices. 
A set of offices, between any two of which a road exists, forms a neighborhood if no others can be added so that the condition is satisfied. 
Frank wonders what is the minimum number of one-way roads that need to be built before the whole city becomes a neighborhood.

Input format
The first line contains a pair of integers n and m (1 ≤ n ≤ 105, 0 ≤ m ≤ 105) - the number of vertices and edges of the given oriented graph.
The next m lines contain descriptions of edges, one per line. Each line contains two integers a and b (1 ≤ a, b ≤ n) - the beginning and the end of the edge.

Output format
Output one number - the number of roads you need to add to make the whole city one neighborhood.

Sample 1
Input	  Output
2 1       1
1 2

Sample 2
Input 	Output
4 3       2
1 2
3 2
2 4

Sample 3
Input  	Output
5 4       2
1 2
3 2
2 4
2 5

Notes:
The numbering is from 1. Loops are allowed.
*/

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
