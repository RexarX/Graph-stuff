#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::vector<int> steps(n + 1);
  std::vector<int> dp(n + 1);
  std::vector<int> path;

  for (int i = 1; i <= n; ++i) {
    std::cin >> steps[i];
  }

  dp[1] = steps[1];
  if (n > 1) {
    dp[2] = steps[2] + std::max(0, dp[1]);
  }

  for (int i = 3; i <= n; ++i) {
    dp[i] = steps[i] + std::max(dp[i - 1], dp[i - 2]);
  }

  int current = n;
  while (current > 0) {
    path.push_back(current);
    if (current == 1 || dp[current - 1] > dp[current - 2]) {
      --current;
    }
    else { current -= 2; }
  }

  std::cout << dp[n] << '\n';
  for (auto it = path.rbegin(); it != path.rend(); ++it) {
    std::cout << *it << ' ';
  }

  return 0;
}