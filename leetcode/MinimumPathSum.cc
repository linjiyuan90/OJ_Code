class Solution {
public:
  int minPathSum(vector<vector<int>>& grid) {
    if (grid.empty()) {
      return 0;
    }
    // sum[i][j] = min(sum[i-1][j], sum[i][j-1]) + grid[i][j]
    // use rolling arry to optimize space
    int n = grid.size(), m = grid.front().size();
    std::vector<std::vector<int>> sum(2, std::vector<int>(m));
    int pre = 0, now = 1;
    // note this initilization
    std::partial_sum(grid.front().begin(), grid.front().end(), sum[pre].begin());
    for (int i = 1; i < n; ++i) {
      sum[now][0] = sum[pre][0] + grid[i][0];
      for (int j = 1; j < m; ++j) {
        sum[now][j] = std::min(sum[pre][j], sum[now][j-1]) + grid[i][j];
      }
      std::swap(now, pre);
    }
    return sum[pre][m-1];
  }
};
