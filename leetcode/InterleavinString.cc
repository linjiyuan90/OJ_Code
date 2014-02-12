class Solution {
public:
  // note empty string!!
  bool isInterleave(std::string s1, std::string s2, std::string s3) {
    int n = s1.length(), m = s2.length();
    if (n + m != s3.length()) {
      return false;
    }
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m+1));
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= m; ++j) {
	if (i == 0 && j == 0) {
	  dp[i][j] = true;
	}
	if (i > 0 && dp[i-1][j] && s3[i+j-1] == s1[i-1]) {
	  dp[i][j] = true;
	}
	if (j > 0 && dp[i][j-1] && s3[i+j-1] == s2[j-1]) {
	  dp[i][j] = true;
	}
      }
    }
    return dp[n][m];
  }
};
