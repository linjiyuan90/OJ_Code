class Solution {
public:
  int minimumTotal(std::vector<std::vector<int>> &triangle) {
    if (triangle.empty()) {
      return 0;
    }
    // dp[i][j] = val[i][j] + min(dp[i+1][j], dp[i+1][j+1])
    std::vector<int> ans;
    std::copy(triangle.back().begin(),
	      triangle.back().end(),
	      std::back_inserter(ans));
    for (int i = triangle.size() - 2; i >= 0; --i) {
      for (int j = 0; j <= i; ++j) {
	ans[j] = std::min(ans[j], ans[j+1]) + triangle[i][j];
      }
    }
    return ans[0];
  }
};
