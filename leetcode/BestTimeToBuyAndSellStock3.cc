class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    if (prices.empty()) {
      return 0;
    }

    // let index in [1, n]
    // let dp[i] = prices[i] - min{prices[j]}, j <= i
    // one transactions:
    // dp[i] = prices[i] - min{prices[j]}
    // two transactions:
    // max{dp[j-1] + prices[i] - min{prices[k]}}, j <= k <= i
    // = prices[i] + max{dp[j-1] + max{-prices[k]}
    // = prices[i] + max{dp[j-1] - prices[k]}

    int ans = 0;
    int min_p = prices[0], max_dp = 0, max_dp_p = -prices[0];
    for (int i = 1; i < prices.size(); ++i) {
      min_p = std::min(min_p, prices[i]);
      max_dp_p = std::max(max_dp_p, max_dp - prices[i]);
      max_dp = std::max(max_dp, prices[i] - min_p);
      // one transactions
      ans = std::max(ans, max_dp);
      // two transactions
      ans = std::max(ans, prices[i] + max_dp_p);
    }
    return ans;
  }
};


// Another method is to dp forward and backward
// max{forward[i] + backward[i+1]}
