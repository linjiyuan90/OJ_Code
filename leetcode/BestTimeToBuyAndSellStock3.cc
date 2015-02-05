class Solution {
public:
  int maxProfit(vector<int> &prices) {
    if (prices.empty()) {
      return 0;
    }
    int n = prices.size();
    std::vector<int> left(n), right(n);
    for (int i = 1, min = prices[0]; i < n; ++i) {
      left[i] = std::max(left[i-1], prices[i] - min);
      min = std::min(min, prices[i]);
    }
    for (int i = n - 2, max = prices[n-1]; i >= 0; --i) {
      right[i] = std::max(right[i+1], max - prices[i]);
      max = std::max(max, prices[i]);
    }
    int ans = left[n-1];
    for (int i = 0; i < n - 1; ++i) {
      ans = std::max(ans, left[i] + right[i+1]);
    }
    return ans;
  }
};
