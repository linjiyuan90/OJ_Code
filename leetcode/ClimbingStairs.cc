class Solution {
  std::vector<int> dp{1, 1, 2};
    
public:
  int climbStairs(int n) {
    if (dp.size() > n) {
      return dp[n];
    }
    int ans = climbStairs(n-1) + climbStairs(n-2);
    dp.push_back(ans);
    return ans;
  }
};
