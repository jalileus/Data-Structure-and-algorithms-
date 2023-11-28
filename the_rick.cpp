#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <vector>

template <class T>
class Graph {
 public:
  Graph(T n);
  ~Graph();
  void ConstructUniverse(T a, T b);
  T Dijkstra(T source, T target);

 private:
  T v_;
  std::list<std::pair<T, T>>* adj_;
};

template <class T>
Graph<T>::Graph(T n) : v_(n) {
  adj_ = new std::list<std::pair<T, T>>[v_];
}

template <class T>
Graph<T>::~Graph() {
  delete[] adj_;
}

template <class T>
void Graph<T>::ConstructUniverse(T a, T b) {
  for (T z = 0; z < v_; z++) {
    T universe_1 = (z + 1) % v_;
    T universe_2 = ((z * z) + 1) % v_;
    adj_[z].push_back({universe_1, a});
    adj_[z].push_back({universe_2, b});
  }
}

template <class T>
T Graph<T>::Dijkstra(T source, T target) {
  std::vector<T> distance(v_, std::numeric_limits<T>::max());
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
          distance[u] + weight < distance[v]) {
        distance[v] = distance[u] + weight;
        pq.push({distance[v], v});
      }
      if (u == target) {
        return distance[u];
      }
    }
  }
  return distance[target];
}

int main() {
  uint64_t lemonade_a, lemonade_b, planets, source, target;
  std::cin >> lemonade_a >> lemonade_b >> planets >> source >> target;
  Graph<uint64_t> my_graph(planets);
  my_graph.ConstructUniverse(lemonade_a, lemonade_b);
  std::cout << my_graph.Dijkstra(source, target) << std::endl;
  return 0;
}