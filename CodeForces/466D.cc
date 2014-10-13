/*
  Very interesting solution!!!
  
  Given a sequence, at each time, choose an interval and increase 1 of all the value in the interval.
  Constraint is for two interval [l1, r1], [l2, r2], need to satisfy: l1 != l2 && r1 != r2.
  Note that r1 = l2 is possible.
  Find the total ways that make all vals = h.
  n, h <= 2000, ai <= 2000

  http://codeforces.com/blog/entry/13758
  dp[i][open] be the ways of cover prefix 1..i to make it equal h and remain after i-th element *open*
  segments that are not closed.
  Answer is dp[n][0].

  At i, options are:
  1) [, open one new
  2) ], close one
  3) [], adding one unit segment
  4) ][, close and open one new
  5) -, do nothing

  First, a[i] + open = h or h-1, otherwise, no such ways.

  if a[i] + open = h
    dp[i][open] = dp[i-1][open] + dp[i-1][open-1]
    // -, [
  if a[i] + open = h-1
    dp[i][open] = dp[i-1][open+1]*(open+1) + dp[i-1][open]*open + dp[i-1][open]
    // ]: close one of [, there are open+1 options
    // ][: close one of [, and new one, there are open options
    // []: new a unit one

  Init: dp[1][0] = a[i] == h || a[i] == h-1, dp[1][1] = a[i] == h-1
*/
#include "iostream"
#include "vector"
#include "algorithm"
#include "map"

const int Mod = 1000000007;

int totalIncreaseWays(const std::vector<int>& seq, int h) {
  if (seq.empty()) {
    return 1;
  }
  int n = seq.size();
  std::vector<std::vector<int>> dp(n, std::vector<int>(h+1));
  dp[0][0] = seq[0] == h || seq[0] == h-1;
  dp[0][1] = seq[0] == h-1;
  for (int i = 1; i < n; ++i) {
    int open = h - seq[i];
    dp[i][open] = dp[i-1][open];
    if (open > 0) {
      dp[i][open] += dp[i-1][open-1];
      dp[i][open] %= Mod;
    }
    open = h - seq[i] - 1;
    if (open >= 0) {
      dp[i][open] = (static_cast<int64_t>(dp[i-1][open+1])*(open+1) % Mod +
                     static_cast<int64_t>(dp[i-1][open])*open % Mod +
                     dp[i-1][open]) % Mod;
    }
  }
  return dp[n-1][0];
}

int main() {
  for (int n, h; std::cin >> n >> h;) {
    std::vector<int> seq(n);
    for (auto& v : seq) {
      std::cin >> v;
    }
    std::cout << totalIncreaseWays(seq, h) << std::endl;
  }
  return 0;
}
