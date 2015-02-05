class Solution {
public:
  int minDistance(std::string word1, std::string word2) {
    int n = word1.size(), m = word2.size();
    std::vector<std::vector<int>> dp(2, std::vector<int>(m + 1, 0));
    int prev = 0, now = 1;
    std::iota(dp[prev].begin(), dp[prev].end(), 0);
    for (int i = 0; i < n; ++i) {
      dp[now][0] = i + 1;
      for (int j = 0; j < m; ++j) {
        dp[now][j+1] = dp[prev][j] + (word1[i] != word2[j]);
        dp[now][j+1] = std::min(dp[now][j+1], dp[now][j] + 1);
        dp[now][j+1] = std::min(dp[now][j+1], dp[prev][j+1] + 1);
      }
      std::swap(prev, now);
    }
    return dp[prev][m];
  }
};


