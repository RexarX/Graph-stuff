#include <iostream>
#include <numeric>

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
    
  int a(0), b(0);
  std::cin >> a >> b;
    
  std::cout << std::gcd(a, b);
    
  return 0;
}