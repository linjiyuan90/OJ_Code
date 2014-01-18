
class Solution {
public:
  int numDistinct(std::string S, std::string T) {
    int n = S.size(), m = T.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
      dp[i][0] = 1;  // don't forget this
      for (int j = 1; j <= m; ++j) {
	if (S[i-1] == T[j-1]) {
	  dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
	} else {
	  dp[i][j] = dp[i-1][j];
	}
      }
    }
    return dp[n][m];
  }
};
