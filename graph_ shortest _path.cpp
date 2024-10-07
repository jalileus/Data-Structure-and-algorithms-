/*
Time limit	2.5 seconds
Memory limit	256Mb
Input	standard input or input.txt
Output	standard output or output.txt

problem :
Rick and Morty are once again roaming the universes, but they decided to limit themselves to only those whose numbers are less than M. 
They can teleport from universe z to universe (z+1) mod M for a bottles of lemonade or to universe (z2+1) mod M for b bottles of lemonade. 
Rick and Morty want to get from universe x to universe y. How many bottles of lemonade will Rick give for such a trip if he wants to spend as little as possible?

Input format
A line in a row contains the number of bottles a for the first type of teleportation, the number of bottles b for the second type of teleportation, 
the number of universes M, the number of the starting universe x, the number of the final universe y (0 ≤ a, b ≤ 100, 1 ≤ M ≤ 106, 0 ≤ x, y < M).

Output format
It is required to find a single number — the number of bottles of lemonade that Rick will give for such a trip.

Sample 1
Input	
3 14 15 9 9
Output
0

Sample 2
Input	
6 1 5 2 3
Output
6

Sample 3
Input	
6 1 5 2 1
Output
2
*/

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
