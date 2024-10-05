#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

static std::vector<int> findPath(int m, int n, const std::vector<std::vector<int>>& matrix)
{
  std::vector<std::vector<int>> dp(m, std::vector<int>(n, std::numeric_limits<int>::max()));
  std::vector<std::vector<int>> path(m, std::vector<int>(n, -1));

  for (int i = 0; i < m; ++i) {
    dp[i][0] = matrix[i][0];
  }

  for (int col = 1; col < n; ++col) {
    for (int row = 0; row < m; ++row) {
      for (int direction = -1; direction <= 1; ++direction) {
        int previousRow = row + direction;
        if (previousRow >= 0 && previousRow < m) {
          int cost = dp[previousRow][col - 1] + matrix[row][col];
          if (cost < dp[row][col] || (cost == dp[row][col] && previousRow < path[row][col])) {
            dp[row][col] = cost;
            path[row][col] = previousRow;
          }
        }
      }
    }
  }

  auto min = std::min_element(dp.begin(), dp.end(),
    [n](const auto& row1, const auto& row2) {
      return row1[n - 1] < row2[n - 1]; 
    });

  int endRow = std::distance(dp.begin(), min);

  std::vector<int> minPath(n);
  for (int i = n - 1; i >= 0; --i) {
    minPath[i] = endRow + 1;
    if (i > 0) { endRow = path[endRow][i]; }
  }

  return minPath;
}

int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);

  int m(0), n(0);
  std::cin >> m >> n;

  std::vector<std::vector<int>> matrix(m, std::vector<int>(n));
  for (auto& row : matrix) {
    for (int& value : row) {
      std::cin >> value;
    }
  }

  std::vector<int> path = findPath(m, n, matrix);

  for (int value : path) {
    std::cout << value << ' ';
  }
  std::cout << '\n';

  int cost = 0;
  for (int i = 0; i < n; ++i) {
    cost += matrix[path[i] - 1][i];
  }
  std::cout << cost;

  return 0;
}