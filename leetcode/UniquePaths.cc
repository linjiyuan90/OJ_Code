class Solution {
public:
  int uniquePaths(int m, int n) {
    // C(m+n, n)
    std::vector<std::vector<int>> cnt(2, std::vector<int>(n));
    int pre = 0, now = 1;
    std::fill(cnt[pre].begin(), cnt[pre].end(), 1);
    for (int i = 1; i < m; ++i) {
      cnt[now][0] = 1;
      for (int j = 1; j < n; ++j) {
        cnt[now][j] = cnt[now][j-1] + cnt[pre][j];
      }
      std::swap(now, pre);
    }
    return cnt[pre][n-1];
  }
};
