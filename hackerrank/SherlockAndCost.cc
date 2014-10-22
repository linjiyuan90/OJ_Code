/*
  Given B, you can choose Ai in [1, Bi]. What's the maximal: ∑|Ai - A{i-1}|
  N <= 100000, Bi <= 100
  
  Since Bi is small, dp it: dp[n][ai]
*/
#include "vector"
#include "iostream"
#include "algorithm"

const int MaxB = 100;
const int MaxN = 100000;

int main() {
  std::ios::sync_with_stdio(false);
  std::vector<std::vector<int>> dp(MaxN, std::vector<int>(MaxB + 1));
  int T, n;
  for (std::cin >> T; T--;) {
    std::cin >> n;
    std::vector<int> B(n);
    for (auto& b : B) {
      std::cin >> b;
    }
    for (int i = 1; i < n; ++i) {
      std::fill(dp[i].begin(), dp[i].end(), 0);
      // dp[i][ai] = max{dp[i-1][a{i-1}] + |a{i-1} - ai|}
      //           = max{dp[i-1][a{i-1}] + a{i-1} - ai} a{i-1} > ai
      //             max{dp[i-1][a{i-1}] - a{i-1} + ai} a{i-1} < ai
      
      // a{i-1} < ai
      int v = -1;
      for (int ai = 1; ai <= B[i]; ++ai) {
        if (ai <= B[i-1]) {
          v = std::max(v, dp[i-1][ai] - ai);
        }
        dp[i][ai] = std::max(dp[i][ai], v + ai);
      }
      // a{i-1} > ai
      v = 1;
      for (int ai_1 = B[i-1]; ai_1 > B[i]; --ai_1) {
        v = std::max(v, dp[i-1][ai_1] + ai_1);
      }
      for (int ai = B[i]; ai >= 1; --ai) {
        if (ai <= B[i-1]) {
          v = std::max(v, dp[i-1][ai] + ai);
        }
        dp[i][ai] = std::max(dp[i][ai], v - ai);
      }
    }
    std::cout << *std::max_element(dp[n-1].begin(), dp[n-1].end()) << std::endl;
  }
  return 0;
}
