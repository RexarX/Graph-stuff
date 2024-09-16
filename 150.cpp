#include <iostream>
#include <vector>
#include <queue>
 
static int bfs(int vertex, const std::vector<std::vector<int>>& matrix)
{
  std::vector<bool> visited(matrix.size(), false);
  std::queue<int> queue;
  int cnt = 0;
 
  queue.push(vertex);
  visited[vertex] = true;
  while (!queue.empty()) {
    for (int i = 0; i < matrix.size(); ++i) {
      if (matrix[queue.front()][i] && !visited[i]) {
        visited[i] = true;
        queue.push(i);
      }
    }
    queue.pop();
    ++cnt;
  }
 
  return --cnt;
}
 
int main()
{
  std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
 
  int n(0), s(0);
  std::cin >> n >> s;
 
  std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
  for (auto& row : matrix) {
    for (int& value : row) {
      std::cin >> value;
    }
  }
 
  std::cout << bfs(--s, matrix);
 
  return 0;
}
