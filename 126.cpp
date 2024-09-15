#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
 
int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
     
  int n = 0;
  std::cin >> n;
 
  std::vector<std::vector<int>> dist(n, std::vector<int>(n));
  for (auto& row : dist) {
    for (int& distance : row) {
      std::cin >> distance;
    }
  }
 
  int minRoute = std::numeric_limits<int>::max();
 
  for (int i = 0; i < n - 2; ++i) {
    for (int j = i + 1; j < n - 1; ++j) {
      for (int k = j + 1; k < n; ++k) {
        int currentRoute = dist[i][j] + dist[j][k] + dist[k][i];
        minRoute = std::min(minRoute, currentRoute);
      }
    }
  }
 
  std::cout << minRoute;
 
  return 0;
}