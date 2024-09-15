#include <iostream>

int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);

  int n = 0;
  long long first(0), second(0);

  std::cin >> n;
  std::cin >> first >> second;

  while (first != second) {
    if (first > second) { first /= 2; }
    else { second /= 2; }
  }

  std::cout << first;

  return 0;
}