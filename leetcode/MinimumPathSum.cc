class Solution {
public:
  int minPathSum(std::vector<std::vector<int>> &grid) {
    // dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
    int n = grid.size(), m = grid[0].size();
    std::vector<std::vector<int>> dp(2, std::vector<int>(m, INT_MAX));
    int now = 0, prev = 1;
    dp[prev][0] = 0;
    for (int i = 0; i < n; ++i) {
      dp[now][0] = dp[prev][0] + grid[i][0];
      for (int j = 1; j < m; ++j) {
        dp[now][j] = std::min(dp[prev][j], dp[now][j-1]) + grid[i][j];
      }
      std::swap(now, prev);
    }
    return dp[prev][m-1];
  }
};
