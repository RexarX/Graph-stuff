#include <iostream>
#include <vector>
 
int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
 
  int vertices = 0;
  std::cin >> vertices;
  std::vector<std::vector<int>> graph(vertices);
 
  bool path = false;
  for (auto& vertex : graph) {
    for (int j = 0; j < vertices; ++j) {
      std::cin >> path;
      if (path) { vertex.push_back(j); }
    }
  }
 
  std::vector<int> colors(vertices);
  for (auto& color : colors) {
    std::cin >> color;
  }
 
  int badCount = 0;
  for (int vertice = 0; vertice < graph.size(); ++vertice) {
    for (int edge : graph[vertice]) {
      if (colors[vertice] != colors[edge]) { ++badCount; }
    }
  }
 
  std::cout << badCount / 2;
     
  return 0;
}