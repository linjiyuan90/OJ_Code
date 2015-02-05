class Solution {
public:
  int minimumTotal(vector<vector<int> > &triangle) {
    std::vector<int> min_sum;
    std::copy(triangle.back().begin(), triangle.back().end(), std::back_inserter(min_sum));
    for (int i = triangle.size() - 2; i >= 0; --i) {
      for (int j = 0, m = triangle[i].size(); j < m; ++j) {
	min_sum[j] = std::min(min_sum[j], min_sum[j+1]) + triangle[i][j];
      }
    }
    return min_sum.front();
  }
};
