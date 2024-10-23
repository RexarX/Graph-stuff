#include <iostream>
#include <vector>
#include <numeric>

static void build_tree(std::vector<int>& tree, const std::vector<int>& arr, int node, int start, int end)
{
  if (start == end) {
    tree[node] = arr[start];
    return;
  }

  int mid = (start + end) / 2;
  build_tree(tree, arr, 2 * node + 1, start, mid);
  build_tree(tree, arr, 2 * node + 2, mid + 1, end);
  tree[node] = std::gcd(tree[2 * node + 1], tree[2 * node + 2]);
}

static int query_tree(const std::vector<int>& tree, int node, int start, int end, int l, int r)
{
  if (l > end || r < start) { return 0; }
  if (l <= start && r >= end) { return tree[node]; }

  int mid = (start + end) / 2;
  int left = query_tree(tree, 2 * node + 1, start, mid, l, r);
  int right = query_tree(tree, 2 * node + 2, mid + 1, end, l, r);

  if (left == 0) { return right; }
  if (right == 0) { return left; }

  return std::gcd(left, right);
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::vector<int> numbers(n);
  for (int& value : numbers) {
    std::cin >> value;
  }

  std::vector<int> tree(4 * n);
  build_tree(tree, numbers, 0, 0, n - 1);

  int m = 0;
  std::cin >> m;

  for (int i = 0; i < m; ++i) {
    int l(0), r(0);
    std::cin >> l >> r;
    --l; --r;

    std::cout << query_tree(tree, 0, 0, n - 1, l, r) << ' ';
  }

  return 0;
}
