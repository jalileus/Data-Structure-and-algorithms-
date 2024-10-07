/*
Time limit	1 second
Memory limit	256.0 MB
Input	stdin or input.txt
Output	stdout or output.txt
Rick needs to get to an inter-universe conference. He pays for each teleportation with bottles of lemonade, 
so he wants to spend them on travelling as little as possible (he is going to the conference after all!). 
However, after K flights in a row, Rick gets very nauseous and goes to bed for the day. He knows all the teleportations that exist. 
Now Rick wants to find a way (the lowest cost in lemonade bottles), given that teleportation takes no time, and the conference is 10 minutes away (so he can make no more than K flights)!

Input format
The first line contains the number of universes N, the number of existing teleportations M, the number of consecutive flights K, Rick's universe number S, 
and the conference universe number F (2 ≤ N ≤ 300, 1 ≤ M ≤ 10^5, 1 ≤ K ≤ 300, 1 ≤ S ≤ N, 1 ≤ F ≤ N).
Next comes M lines specifying the teleportations. The i-th line contains three natural numbers: 
Si, Fi and Pi, where Si is the number of the universe from which the i-th teleportation leads, 
Fi is the number of the universe to which the i-th teleportation leads, Pi is the cost of the i-th teleportation. 1 ≤ Si ≤ N, 1 ≤ Fi ≤ N, 1 ≤ Pi ≤ 10^6. 

Output format
Output one number - the minimum cost of a journey suitable for the professor. If the professor cannot get to the conference in K nights, output the number -1.

Sample 1
Input           	Output
5 7 2 4 1          4
1 2 6
5 1 1
4 1 9
4 5 3
4 3 2
2 5 7
3 5 1

Sample 2
Input           	Output
3 3 1 1 3          -1
1 2 4
2 3 5
3 1 6

Notes:
There are no teleporters leading from one universe to its own, within the scope of this journey ;)
*/

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
