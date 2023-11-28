#include <iostream>
#include <limits>
#include <queue>
#include <vector>

template <class T>
class Graph {
 public:
  Graph(T n, T target, T number_of_flights);
  ~Graph();
  void CreatUniverse(T first_world, T second_world, T lemonade_value);
  void Relax(T u);
  T Dikjstra(T source);

 private:
  T worlds_;
  std::vector<std::vector<std::pair<T, T>>> adj_;
  std::priority_queue<std::pair<T, T>, std::vector<std::pair<T, T>>,
                      std::greater<std::pair<T, T>>>
      pq_;
  std::vector<T> distance_;
  std::vector<T> path_;
  T conference_target_;
  T flights_;
};

template <class T>
Graph<T>::Graph(T n, T target, T number_of_flights)
    : worlds_(n),
      adj_(n),
      conference_target_(target),
      flights_(number_of_flights) {
  distance_.resize(worlds_, std::numeric_limits<T>::max());
  path_.resize(worlds_, 0);
}

template <class T>
Graph<T>::~Graph() {}

template <class T>
void Graph<T>::CreatUniverse(T first_world, T second_world, T lemonade_value) {
  adj_[first_world].push_back({second_world, lemonade_value});
}

template <class T>
void Graph<T>::Relax(T u) {
  for (const auto& neighbor : adj_[u]) {
    T v = neighbor.first;
    T weight = neighbor.second;
    if (distance_[u] != std::numeric_limits<T>::max() &&
        distance_[u] + weight < distance_[v] &&
        ((path_[u] + 1) < flights_ || v == conference_target_)) {
      distance_[v] = distance_[u] + weight;
      pq_.push({distance_[v], v});
      path_[v] = path_[u] + 1;
    }
  }
}

template <class T>
T Graph<T>::Dikjstra(T source) {
  path_[source] = 0;
  distance_[source] = 0;
  pq_.push({0, source});
  while (!pq_.empty()) {
    T u = pq_.top().second;
    pq_.pop();
    Relax(u);
  }
  if (path_[conference_target_] != 0) {
    return distance_[conference_target_];
  }
  return -1;
}

int main() {
  int64_t worlds, teleportations, flights, rick_location, conference_location;
  std::cin >> worlds >> teleportations >> flights >> rick_location >>
      conference_location;
  int64_t size = worlds + 1;
  Graph<int64_t> my_graph(size, conference_location, flights);
  for (int64_t i = 0; i < teleportations; i++) {
    int64_t first_universe, second_universe, lemonade;
    std::cin >> first_universe >> second_universe >> lemonade;
    my_graph.CreatUniverse(first_universe, second_universe, lemonade);
  }
  if (conference_location == rick_location) {
    std::cout << 0 << std::endl;
    return 0;
  }
  std::cout << my_graph.Dikjstra(rick_location) << std::endl;
  return 0;
}
