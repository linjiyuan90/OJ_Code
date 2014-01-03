class Solution {
public:
  int minDistance(std::string word1, std::string word2) {
    int n = word1.size(), m = word2.size();
    std::vector<std::vector<int>> dp(2, std::vector<int>(m+1, 0));
    int now = 0, prev = 1;
    for (int i = 0; i <= n; ++i) {
      dp[now][0] = i; // don't forget
      for (int j = 1; j <= m; ++j) {
	if (i == 0) {
	  dp[now][j] = j;
	} else {
	  dp[now][j] = dp[prev][j-1] + (word1[i-1] != word2[j-1]);
	  dp[now][j] = std::min(dp[now][j], dp[prev][j] + 1);
	  dp[now][j] = std::min(dp[now][j], dp[now][j-1] + 1);
	}
      }
      std::swap(now, prev);
    }
    return dp[prev][m];
  }
};
