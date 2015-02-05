class Solution {
public:
  int numDistinct(string S, string T) {
    int n = S.length(), m = T.length();
    std::vector<std::vector<int>> dp(2, std::vector<int>(m+1));
    int pre = 0, now = 1;
    dp[pre][0] = 1;
    for (int i = 0; i < n; ++i) {
      dp[now][0] = 1;
      for (int j = 0; j < m; ++j) {
	dp[now][j+1] = dp[pre][j+1] + (S[i] == T[j] ? dp[pre][j] : 0);
      }
      std::swap(pre, now);
    }
    return dp[pre][m];
  }
};
