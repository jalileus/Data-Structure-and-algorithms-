#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

class Graph {
 public:
  Graph(int n);
  ~Graph();
  void CreatUniverse(int universe_1, int universe_2, int probability);
  double Dijkstra(int source, int target);

 private:
  int worlds_;
  std::vector<std::vector<std::pair<int, double>>> adj_;
};

Graph::Graph(int n) : worlds_(n), adj_(n) {}

Graph::~Graph() {}

void Graph::CreatUniverse(int universe_1, int universe_2, int probability) {
  adj_[universe_1].push_back(
      {universe_2, static_cast<double>(probability) / 100.0});
  adj_[universe_2].push_back(
      {universe_1, static_cast<double>(probability) / 100.0});
}

double Graph::Dijkstra(int source, int target) {
  std::vector<double> probabilities(worlds_, 1.01);
  probabilities[source] = 0.0;
  std::priority_queue<std::pair<double, int>,
                      std::vector<std::pair<double, int>>,
                      std::greater<std::pair<double, int>>>
      pq;
  pq.push({0.0, source});
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (u == target) {
      return probabilities[u];
    }
    for (const auto& neighbor : adj_[u]) {
      int v = neighbor.first;
      double edge_prob = neighbor.second;
      double new_prob =
          probabilities[u] + edge_prob - (probabilities[u] * edge_prob);
      if (new_prob < probabilities[v]) {
        probabilities[v] = new_prob;
        pq.push({probabilities[v], v});
      }
    }
  }
  return probabilities[target];
}

int main() {
  int worlds, teleportations, rick_location, target;
  std::cin >> worlds >> teleportations >> rick_location >> target;
  int size = worlds + 1;
  Graph my_graph(size);
  for (int i = 0; i < teleportations; i++) {
    int universe_1, universe_2, probability;
    std::cin >> universe_1 >> universe_2 >> probability;
    my_graph.CreatUniverse(universe_1, universe_2, probability);
  }
  std::cout << std::setprecision(2);
  std::cout << std::noshowpoint << my_graph.Dijkstra(rick_location, target)
            << std::endl;
  return 0;
}