/*
  Given a stack of bricks, each with a score.
  Two players playing a game, at each time, remove 1, 2 or 3 bricks from the top and sum the scores.
  What's the max score the first player can achieve?
*/
#include "algorithm"
#include "numeric"
#include "iostream"
#include "vector"
#include "limits"

int main() {
  int T, n;
  for (std::cin >> T; T--; ) {
    std::cin >> n;
    std::vector<long long> bricks(n);
    for (auto& b : bricks) {
      std::cin >> b;
    }
    // dp[i] = sum[i] - min{dp[j]}, j = i+1..i+3
    // sum[i] = sum{b[i..]}
    std::vector<long long> suffixSum(n);
    // partial_sum take the type of first !!!
    std::partial_sum(bricks.rbegin(), bricks.rend(), suffixSum.rbegin());
    std::vector<long long> dp(n);
    for (int i = n - 1; i >= 0; --i) {
      long long min = std::numeric_limits<long long>::max();
      for (int k = 1; k <= 3 && i + k <= n; ++k) {
        min = std::min(min, i + k == n ? 0 : dp[i+k]);
      }
      dp[i] = suffixSum[i] - min;
    }
    std::cout << dp[0] << std::endl;
  }
  return 0;
}
