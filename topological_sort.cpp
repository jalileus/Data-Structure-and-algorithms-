/*
Time limit	3 seconds
Memory limit	256Mb
Input	standard input or input.txt
Output	standard output or output.txt

problem :
John McClain radios new information about terrorists to a department with n police officers. 
He calls several officers and asks them to spread the information around the department, knowing that each policeman has a connection to certain colleagues. 
John McClain wants the operation to be a success. But if a policeman calls a colleague from whom (perhaps not directly) he received the information, 
the terrorists can trace the call and interfere with the operation. If two officers call one, nothing bad will happen. Help John McClain.
Take NO out if one of the police officers makes a mistake making the call. If all goes well, output YES and the order in which the officers receive the information,
assuming that the officers notify their colleagues in ascending order of their numbers, and that John gives the information to those who cannot be called by any of his colleagues at the beginning.

Input format
The first line contains a pair of integers n and m (1 ≤ n, m ≤ 105) - the number of vertices and edges of the given oriented graph.

The next m lines contain descriptions of edges, one per line. Each line contains two integers a and b (0 ≤ a, b < n) - the beginning and the end of the edge.

Output format
If no such order exists, print "NO" (without quotes).

Otherwise, print "YES" in the first line. In the second line print the permutation of vertex indices (integers from 0 to n - 1) such that for each edge its starting vertex is strictly to the left of its ending vertex.

Sample 1
Input	    Output
4 5        YES
0 2      0 2 1 3 
2 1
1 3
2 3
0 3

Sample 2
Input	    Output
3 3         NO
0 1
1 2
2 0

Sample 3
Input	    Output
2 2        NO
0 1
1 1

Notes:
The numbering is from 0. Loops are allowed.
*/

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
