#include <iostream>
#include <limits>
#include <queue>
#include <vector>

template <class T>
class Graph {
 public:
  Graph(T n);
  ~Graph();
  void CreatUniverse(T world_1, T world_2, T lemonade_value);
  T Dikjstra(T source, T conference_target, T flights);

 private:
  T worlds_;
  std::vector<std::vector<std::pair<T, T>>> adj_;
};

template <class T>
Graph<T>::Graph(T n) : worlds_(n), adj_(n) {}

template <class T>
Graph<T>::~Graph() {}

template <class T>
void Graph<T>::CreatUniverse(T world_1, T world_2, T lemonade_value) {
  adj_[world_1].push_back({world_2, lemonade_value});
}

template <class T>
T Graph<T>::Dikjstra(T source, T conference_target, T flights) {
  std::vector<T> path(worlds_, 0);
  path[source] = 0;
  std::vector<T> distance(worlds_, std::numeric_limits<T>::max());
  distance[source] = 0;
  std::priority_queue<std::pair<T, T>, std::vector<std::pair<T, T>>,
                      std::greater<std::pair<T, T>>>
      pq;
  pq.push({0, source});
  while (!pq.empty()) {
    T u = pq.top().second;
    pq.pop();
    for (const auto& neighbor : adj_[u]) {
      T v = neighbor.first;
      T weight = neighbor.second;
      if (distance[u] != std::numeric_limits<T>::max() &&
          distance[u] + weight < distance[v] &&
          ((path[u] + 1) < flights || v == conference_target)) {
        distance[v] = distance[u] + weight;
        pq.push({distance[v], v});
        path[v] = path[u] + 1;
      }
    }
  }
  if (path[conference_target] != 0) {
    return distance[conference_target];
  }
  return -1;
}

int main() {
  int64_t worlds, teleportations, flights, rick_location, conference_location;
  std::cin >> worlds >> teleportations >> flights >> rick_location >>
      conference_location;
  int64_t size = worlds + 1;
  Graph<int64_t> my_graph(size);
  for (int64_t i = 0; i < teleportations; i++) {
    int64_t universe_1, universe_2, lemonade;
    std::cin >> universe_1 >> universe_2 >> lemonade;
    my_graph.CreatUniverse(universe_1, universe_2, lemonade);
  }
  if (conference_location == rick_location) {
    std::cout << 0 << std::endl;
    return 0;
  }
  std::cout << my_graph.Dikjstra(rick_location, conference_location, flights)
            << std::endl;
  return 0;
}