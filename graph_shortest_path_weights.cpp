/*
Time limit	1 second
Memory limit	256.0 MB
Input	stdin or input.txt
Output	stdout or output.txt

problem :
Now Rick needs to get from the universe with the number S to the universe with the number F. 
He knows all existing teleporters, and it would seem that there is no problem. 
But, it's no secret that in his long life, Rick has had a lot of fights with a lot of people. He knows from personal experience that when teleporting, there is a chance of being made to answer for his words.
If Rick knows the probabilities of being pinned against the wall on all existing teleportations, help him calculate the minimum probability that he will still get in trouble.

Input format
The first line contains the number of universes N (2 ≤ N ≤ 100), the number of existing teleportations M (1 ≤ M ≤ N ⋅ (N - 1) / 2), the starting universe S (1 ≤ S ≤ N) and the final universe F (1 ≤ F ≤ N).
Next, M lines describe teleportations in the format Si, Fi, Pi, 
where Si and Fi are the numbers of universes that the i-th teleportation connects (teleports are bidirectional, 1 ≤ Si, Fi ≤ N), Pi is the probability of being beaten on the i-th teleportation in percent (0 ≤ Pi ≤ 100).

Output format
The probability of being beaten to within 10^(-2)

Sample
Input	        Output
5 7 1 3        0.36
1 2 20
3 4 10
1 5 37
1 3 50
2 3 20
4 5 92
1 4 67

Notes:
In this case it is again assumed that there are no teleports from a universe to the same universe, 
and no two teleports are identical (i.e. with the same initial and final universes). It is guaranteed that the path between S and F always exists.


*/

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
