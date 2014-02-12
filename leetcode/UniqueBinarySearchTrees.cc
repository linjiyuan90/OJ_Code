class Solution {
public:
  int numTrees(int n) {
    std::vector<int> dp(n+1);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
      for (int left = 0; left < i; ++left) {
	dp[i] += dp[left] * dp[i - left - 1];
      }
    }
    return dp[n];
  }
};
