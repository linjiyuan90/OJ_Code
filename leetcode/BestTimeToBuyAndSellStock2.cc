#include "iostream"
#include "algorithm"
#include "vector"

class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    if (prices.empty()) {
      return 0;
    }
    // at i, sell the stock buy in j (j <= i)
    // dp[i] = max{dp[j-1] + prices[i] - prices[j]}
    //       = max{dp[j-1] - prices[j]} + prices[i]
    // ans = dp[n-1]
    // O(n)
    // the dp array can be removed
    std::vector<int> dp(prices.size(), 0);
    int max_dp_price = -prices[0];
    for (size_t ix = 1; ix < prices.size(); ++ix) {
      // this is the situation "buy and sell at ix"
      max_dp_price = max(max_dp_price, dp[ix-1] - prices[ix]);
      dp[ix] = max_dp_price + prices[ix];
    }
    return dp.back();
  }
};
