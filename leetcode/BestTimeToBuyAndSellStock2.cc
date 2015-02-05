class Solution {
public:
  int maxProfit(vector<int> &prices) {
    // once there is an increament, get it
    int ans = 0;
    for (int i = 1, n = prices.size(); i < n; ++i) {
      ans += std::max(prices[i] - prices[i-1], 0);
    }
    return ans;
  }
};
