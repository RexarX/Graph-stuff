#include <iostream>
#include <vector>
#include <queue>

struct Vertex
{
  int vertex;
  int weight;

  bool operator>(const Vertex& other) const {
    return weight > other.weight;
  }
};

static std::vector<int> dijkstra(int start, const std::vector<std::vector<Vertex>>& graph) {
  std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
  distances[start] = 0;

  std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> pq;
  pq.emplace(start, 0);

  while (!pq.empty()) {
    Vertex current = pq.top();
    pq.pop();

    if (current.weight > distances[current.vertex]) { continue; }

    for (const Vertex& neighbor : graph[current.vertex]) {
      int distance = current.weight + neighbor.weight;
      if (distance < distances[neighbor.vertex]) {
        distances[neighbor.vertex] = distance;
        pq.emplace(neighbor.vertex, distance);
      }
    }
  }

  return distances;
}

int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);

  std::vector<std::vector<Vertex>> graph = {
    {{1, 4}, {2, 1}},           // Node 0
    {{3, 1}},                   // Node 1
    {{1, 2}, {3, 5}},           // Node 2
    {{4, 3}},                   // Node 3
    {}                          // Node 4
  };

  int start_node = 0;
  std::vector<int> shortest_distances = dijkstra(start_node, graph);

  std::cout << "Shortest distances from node " << start_node << ":\n";
  for (int i = 0; i < shortest_distances.size(); ++i) {
    std::cout << "To node " << i << ": ";
    if (shortest_distances[i] == std::numeric_limits<int>::max()) {
      std::cout << "Infinity" << '\n';
    }
    else { std::cout << shortest_distances[i] << '\n'; }
  }

  return 0;
}