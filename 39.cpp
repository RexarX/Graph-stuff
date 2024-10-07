#include <iostream>
#include <vector>
 
int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
 
  int n = 0;
  std::cin >> n;
 
  std::vector<int> prices(n);
  for (int& price : prices) {
    std::cin >> price;
  }
 
  std::vector<int> dp(n + 1, 0);
  for (int day = n - 1; day >= 0; --day) {
    int maxProfit = 0;
    for (int sellDay = day; sellDay < n; ++sellDay) {
      int profit = prices[sellDay] * (sellDay - day + 1) + dp[sellDay + 1];
      if (maxProfit < profit) { maxProfit = profit; }
    }
    dp[day] = maxProfit;
  }
 
  std::cout << dp[0];
 
  return 0;
}
