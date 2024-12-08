#include <iostream>
#include <vector>
#include <numeric>
#include <future>
#include <thread>

struct Query {
  int l = 0;
  int r = 0;
};

static void build_tree(std::vector<int>& tree, const std::vector<int>& arr, int node, int start, int end) {
  if (start == end) {
    tree[node] = arr[start];
    return;
  }
    
  int mid = (start + end) / 2;
  build_tree(tree, arr, 2 * node + 1, start, mid);
  build_tree(tree, arr, 2 * node + 2, mid + 1, end);
  tree[node] = std::gcd(tree[2 * node + 1], tree[2 * node + 2]);
}

static int query_tree(const std::vector<int>& tree, int node, int start, int end, int l, int r) {
  if (l > end || r < start) { return 0; }
  if (l <= start && r >= end) { return tree[node]; }
  
  int mid = (start + end) / 2;
  int left = query_tree(tree, 2 * node + 1, start, mid, l, r);
  int right = query_tree(tree, 2 * node + 2, mid + 1, end, l, r);
  
  if (left == 0) { return right; }
  if (right == 0) { return left; }

  return std::gcd(left, right);
}

static std::vector<int> process_batch(const std::vector<int>& tree, const std::vector<Query>& queries, int n, int start, int end) {
  std::vector<int> results(end - start);
  for (int i = start; i < end; ++i) {
    const auto& [l, r] = queries[i];
    results[i - start] = query_tree(tree, 0, 0, n - 1, l, r);
  }
  
  return results;
}

int main() {
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
  
  std::vector<Query> queries(m);
  for (auto& [l, r] : queries) {
    std::cin >> l >> r;
    --l; --r;
  }
  
  int num_threads = std::thread::hardware_concurrency();
  int batch_size = (m + num_threads - 1) / num_threads;
  std::vector<std::future<std::vector<int>>> futures;
  
  for (int i = 0; i < m; i += batch_size) {
    int batch_end = std::min(i + batch_size, m);
    futures.push_back(std::async(
      std::launch::async,
      process_batch,
      std::ref(tree),
      std::ref(queries),
      n, i, batch_end
    ));
  }
  
  for (auto& future : futures) {
    const auto& batch_results = future.get();
    for (int result : batch_results) {
      std::cout << result << ' ';
    }
  }
  
  return 0;
}
