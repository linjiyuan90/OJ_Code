class Solution {
public:
  int climbStairs(int n) {
    // dp[i] = dp[i-1] + dp[i-2];
    // dp[1] = 1;
    // dp[0] = 1;
    int dp[3] = {1, 1, 0};
    for (int i = 2; i <= n; ++i) {
      dp[i%3] = dp[(i-1)%3] + dp[(i-2)%3];
    }
    return dp[n%3];
  }
};

// faster algorithm is to use matrix multiplication
