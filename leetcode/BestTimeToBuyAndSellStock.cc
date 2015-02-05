class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int ans = 0;
    for (int i = 0, n = prices.size(), min; i < n; ++i) {
      if (i == 0) {
	min = prices[i];   
      } else {
	ans = std::max(ans, prices[i] - min);
	min = std::min(min, prices[i]);
      }
    }
    return ans;
  }
};
