/*
Time limit	3 seconds
Memory limit	256Mb
Input	standard input or input.txt
Output	standard output or output.txt

problem :
Leon and Matilda were about to go to the store for milk. Stansfield wants to meet them, so our friends need to do it as quickly as possible. 
What is the minimum number of streets that at least one of the guys will walk through (either Matilda, or Leon, or both together).
We believe that both friends need to get to the store without fail.

Input format
"The first line contains the number of vertices n (1 ≤ n ≤ 105), the number of edges m (0 ≤ m ≤ 105) and the vertex numbers leon, matilda, milk, which contain Leon, Matilda, and a milk shop, respectively.

The next m lines contain the edges of the graph. Each line contains two numbers, separated by a space, if there is an edge between i and j. It is guaranteed that there are no loops and multi-edges in the graph."

Output format
One number is the number of edges.

Sample 1
Input	        Output
3 2 1 2 3      2
1 3
2 3

Sample 2
Input         Output
5 4 1 1 5      4
1 2
2 3
3 4
4 5

Notes:
The graph is connected and undirected. Vertices are numbered from 1.
*/

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
