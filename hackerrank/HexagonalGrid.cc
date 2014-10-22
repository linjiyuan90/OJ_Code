/*
  Fill the grid which may have obstacles.
  
  How to write a general solution?
*/
#include "iostream"
#include "vector"
#include "algorithm"
#include "string"

int main() {
  int T, n;
  for (std::cin >> T; T--; ) {
    std::cin >> n;
    std::string grid[2];
    std::cin >> grid[0] >> grid[1];
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(4));
    // dp[c][mask]
    // if (mask&(1<<i)), means grid[c][i] is filled
    dp[0][3] = 1;
    for (int c = 1; c <= n; ++c) {
      int need = (grid[0][c-1] == '1' ? 1 : 0) + (grid[1][c-1] == '1' ? 2 : 0);
      // do nothing
      dp[c][need] |= dp[c-1][3];
      // 0: --
      // 1:
      if ((need & 1) == 0) {
        dp[c][need|1] |= dp[c-1][2];
      }
      // 0:
      // 1: --
      if ((need & 2) == 0) {
        dp[c][need|2] |= dp[c-1][1];
      }
      // 0: |
      // 1: |
      if ((need & 1) == 0 && (need & 2) == 0) {
        dp[c][3] |= dp[c-1][3];
      }
      // 0:  /
      // 1: /
      if ((need & 1) == 0) {
        dp[c][need|1] |= dp[c-1][1];
      }
  }
  std::cout << (dp[n][3] ? "YES" : "NO") << std::endl;
}
return 0;
}
