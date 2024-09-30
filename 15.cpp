#include <iostream>
 
int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
 
  int size = 0;
  std::cin >> size;
  size *= size;

  int count = 0;
  int num = 0;
  for (int i = 0; i < size; ++i) {
    std::cin >> num;
    if (num) { ++count; }
  }
   
  std::cout << count / 2;
   
  return 0;
}
