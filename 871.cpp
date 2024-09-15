#include <iostream>
#include <vector>
#include <algorithm>
 
int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
 
  int n(0), m(0);
  std::cin >> n >> m;
 
  std::vector<std::pair<int, int>> edges;
 
  int u(0), v(0);
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;
    std::pair<int, int> edge1(u, v);
    std::pair<int, int> edge2(v, u);
 
    auto it = std::find_if(edges.begin(), edges.end(), [edge1, edge2](std::pair<int, int> edge) {
      return edge.first == edge1.first && edge.second == edge1.second ||
             edge.first == edge2.first && edge.second == edge2.second;
    });
 
    if (it == edges.end()) { edges.push_back(edge1); }
  }
 
  edges.size() < n ? std::cout << "NO" : std::cout << "YES";
 
  return 0;
}