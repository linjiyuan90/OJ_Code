/*
  How many ways to build a wall with height n & width m with bricks of
  1*1, 1*2, 1*3, 1*4. The bricks can only be put horizontally.
  And restriction is no vertical line can cut the wall.
*/

#include "vector"
#include "algorithm"
#include "iostream"

const int Mod = 1000000007;
const int MaxM = 1000;

std::vector<int> initWays(int n) {
  std::vector<int> ways(n+1);
  ways[0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= std::min(i, 4); ++j) {
      ways[i] = (ways[i] + ways[i-j]) % Mod; 
    }
  }
  return ways;
}

int pow(int a, int n) {
  if (n == 0) {
    return 1;
  }
  if (n == 1) {
    return a % Mod;
  }
  int64_t ans = pow(a, n/2);
  ans = ans * ans % Mod;
  if (n & 1) {
    ans = ans * a % Mod;
  }
  return ans;
}

int main() {
  auto ways = initWays(MaxM);
  int T, n, m;
  for (std::cin >> T; T--; ) {
    std::cin >> n >> m;
    // total ways is: ways[m] ^ n
    // legal ways is: dp[n, m] = ways[m] ^ n - ∑dp[n, s] * ways[m-s] ^ n, s >= 1
    // dp[n, 1] = 1
    std::vector<int> dp(m+1);
    dp[1] = 1;
    for (int mi = 2; mi <= m; ++mi) {
      dp[mi] = pow(ways[mi], n);
      for (int s = 1; s < mi; ++s) {
        dp[mi] = (dp[mi] - 1ll * dp[s] * pow(ways[mi-s], n) % Mod + Mod) % Mod;
      }
    }
    std::cout << dp[m] << std::endl;
  }
  return 0;
}
