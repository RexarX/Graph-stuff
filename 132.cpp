#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Vertex
{
  int vertex;
  int weight;

  bool operator>(const Vertex& other) const {
    return weight > other.weight;
  }
};

static int dijkstra(int start, int end, const std::vector<std::vector<Vertex>>& graph) {
  std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
  distances[start] = 0;

  std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> pq;
  pq.emplace(start, 0);

  while (!pq.empty()) {
    Vertex current = pq.top();
    pq.pop();

    if (current.vertex == end) { return current.weight; }
    if (current.weight > distances[current.vertex]) { continue; }

    for (const Vertex& neighbor : graph[current.vertex]) {
      int distance = current.weight + neighbor.weight;
      if (distance < distances[neighbor.vertex]) {
        distances[neighbor.vertex] = distance;
        pq.emplace(neighbor.vertex, distance);
      }
    }
  }

  return -1;
}

int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);

  int n(0), s(0), f(0);
  std::cin >> n >> s >> f;

  std::vector<std::vector<Vertex>> graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int weight = 0;
      std::cin >> weight;
      if (weight != -1) { graph[i].emplace_back(j, weight); }
    }
  }

  std::cout << dijkstra(--s, --f, graph);

  return 0;
}