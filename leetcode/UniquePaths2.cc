class Solution {
public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid.empty()) {
      return 0;
    }
    // cnt[i][j] = cnt[i-1][j] + cnt[i][j-1], if grid[i][j] is not obstacle
    // cnt[i][j] = 0
    int n = obstacleGrid.size(), m = obstacleGrid.front().size();
    std::vector<std::vector<int>> cnt(2, std::vector<int>(m));
    int pre = 0, now = 1;
    int firstObstacle = 
      std::find(obstacleGrid.front().begin(), obstacleGrid.front().end(), 1) - obstacleGrid.front().begin();
    std::fill(cnt[pre].begin(), cnt[pre].begin() + firstObstacle, 1);
    for (int i = 1; i < n; ++i) {
      cnt[now][0] = obstacleGrid[i][0] ? 0 : cnt[pre][0];
      for (int j = 1; j < m; ++j) {
        if (obstacleGrid[i][j]) {
          cnt[now][j] = 0;
        } else {
          cnt[now][j] = cnt[pre][j] + cnt[now][j-1];
        }
      }
      std::swap(pre, now);
    }
    return cnt[pre][m-1];
  }
};
