#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 100000;

static bool has_negative_cycle(std::vector<std::vector<int>>& graph)
{
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph.size(); ++j) {
      for (int k = 0; k < graph.size(); ++k) {
        if (graph[i][k] < INF && graph[k][j] < INF) {
          graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
        }
      }
    }
  }

  for (int i = 0; i < graph.size(); ++i) {
    if (graph[i][i] < 0) { return true; }
  }

  return false;
}

int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::vector<std::vector<int>> graph(n, std::vector<int>(n));
  for (auto& vec : graph) {
    for (int& value : vec) {
      std::cin >> value;
    }
  }

  std::cout << (has_negative_cycle(graph) ? "YES" : "NO");

  return 0;
}
