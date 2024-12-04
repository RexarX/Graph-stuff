#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <algorithm>

struct Query {
  int l = 0;
  int r = 0;
};

static void build_tree(std::vector<int>& tree, const std::vector<int>& arr,
                       int node, int start, int end) {
  if (start == end) {
    tree[node] = arr[start];
    return;
  }

  int mid = (start + end) / 2;
  build_tree(tree, arr, 2 * node + 1, start, mid);
  build_tree(tree, arr, 2 * node + 2, mid + 1, end);
  tree[node] = std::gcd(tree[2 * node + 1], tree[2 * node + 2]);
}

static int query_tree(const std::vector<int>& tree, int node, int start,
                      int end, int l, int r) {
  if (l > end || r < start) { return 0; }
  if (l <= start && r >= end) { return tree[node]; }

  int mid = (start + end) / 2;
  int left = query_tree(tree, 2 * node + 1, start, mid, l, r);
  int right = query_tree(tree, 2 * node + 2, mid + 1, end, l, r);

  if (left == 0) { return right; }
  if (right == 0) { return left; }

  return std::gcd(left, right);
}

static std::vector<int> process_queries_multithreaded(const std::vector<int>& tree,
                                                      const std::vector<Query>& queries, int n) {
  unsigned int num_threads = std::thread::hardware_concurrency();
  num_threads = num_threads == 0 ? 4 : num_threads;

  std::vector<int> results(queries.size());

  std::vector<std::thread> threads;

  int total_queries = queries.size();
  int batch_size = (total_queries + num_threads - 1) / num_threads;

  auto worker = [&](int start, int end) {
    for (int i = start; i < end; ++i) {
      const auto [l, r] = queries[i];
      int gcd_result = query_tree(tree, 0, 0, n - 1, l, r);
      results[i] = gcd_result;
    }
  };

  for (unsigned int i = 0; i < num_threads && i * batch_size < total_queries; ++i) {
    int thread_start = i * batch_size;
    int thread_end = std::min(static_cast<int>((i + 1) * batch_size), total_queries);

    threads.emplace_back(worker, thread_start, thread_end);
  }

  for (std::thread& thread : threads) {
    thread.join();
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

  std::vector<int> results = process_queries_multithreaded(tree, queries, n);
  for (int result : results) {
    std::cout << result << ' ';
  }

  return 0;
}
