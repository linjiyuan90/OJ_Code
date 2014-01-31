class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    if (prices.empty()) {
      return 0;
    }
    int ans = 0;
    int min = prices[0];
    for (size_t ix = 1; ix < prices.size(); ++ix) {
      ans = std::max(ans, prices[ix] - min);
      min = std::min(min, prices[ix]);
    }
    return ans;
  }
};
