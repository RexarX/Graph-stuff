#include <iostream>
#include <vector>
 
int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
   
  int vertices(0), edges(0);
   
  std::cin >> vertices >> edges;
  std::vector<std::vector<int>> graph(vertices);
   
  int departure(0), destination(0);
  for (int i = 0; i < edges; ++i) {
    std::cin >> departure >> destination;
    --departure; --destination;
    graph[departure].push_back(destination);
    graph[destination].push_back(departure);
  }
   
  for (auto& vertex : graph) {
    std::cout << vertex.size() << '\n';
  }
   
  return 0;
}
