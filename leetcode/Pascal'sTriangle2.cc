class Solution {
public:
  std::vector<int> getRow(int rowIndex) {
    // dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
    std::vector<int> ans;
    for (int i = 0; i <= rowIndex; ++i) {
      ans.push_back(1);
      for (int j = ans.size() - 2; j > 0; --j) {
	ans[j] += ans[j-1];
      }
    }
    return ans;
  }
};
