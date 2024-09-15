#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

struct PairHash
{
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& p) const
  {
    auto min = std::min(p.first, p.second);
    auto max = std::max(p.first, p.second);

    std::size_t h = 2166136261u;
    h ^= min;
    h *= 16777619u;
    h ^= max;
    h *= 16777619u;

    return h;
  }
};

struct PairEqual
{
  template <class T1, class T2>
  inline bool operator()(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) const {
    return (p1.first == p2.first && p1.second == p2.second) ||
           (p1.first == p2.second && p1.second == p2.first);
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);

  int n(0), m(0);
  std::cin >> n >> m;

  std::unordered_set<std::pair<int, int>, PairHash, PairEqual> edges;

  int u(0), v(0);
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;
    edges.emplace(u, v);
  }

  edges.size() < n ? std::cout << "NO" : std::cout << "YES";

  return 0;
}