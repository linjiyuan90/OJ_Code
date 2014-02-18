class Solution {
public:
  int uniquePathsWithObstacles(std::vector<std::vector<int>> &obstacleGrid) {
    if (obstacleGrid.empty()) {
      return 0;
    }
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();
    std::vector<std::vector<int>> dp(2, std::vector<int>(m));
    int now = 0, prev = 1;
    dp[prev][0] = 1;
    for (int i = 0; i < n; ++i) {
      dp[now].assign(m, 0);
      for (int j = 0; j < m; ++j) {
	if (obstacleGrid[i][j] == 1) {
	  dp[now][j] = 0;
	} else {
	  dp[now][j] = dp[prev][j];
	  if (j > 0) {
	    dp[now][j] += dp[now][j-1];
	  }
	}
      }
      std::swap(now, prev);
    }
    return dp[prev][m-1];
  }
};

// There is another solution using inclusion-exclusion principle if the number 
// of obstacles is small and the dimension is large.
