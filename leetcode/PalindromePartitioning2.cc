class Solution {
public:
  // O(n^2)
  int minCut(std::string s) {
    int n = s.length();
    std::vector<int> dp(n + 1, n - 1);
    // note use -1 to offset
    dp[0] = -1;
    for (int ix = 0; ix < n; ++ix) {
      // ix as middle of the palindrome
      for (int j = 0; ix - j >= 0 && ix + j < n && s[ix-j] == s[ix+j]; ++j) {
	dp[ix+j+1] = std::min(dp[ix+j+1], dp[ix-j] + 1);
      }
      // ix as the right bound of the left part of the palindrome
      for (int j = 1; ix - j + 1 >= 0 && ix + j < n && s[ix-j+1] == s[ix+j];
	   ++j) {
	dp[ix+j+1] = std::min(dp[ix+j+1], dp[ix-j+1] + 1);
      }
    }
    return dp[n];
  }
};
