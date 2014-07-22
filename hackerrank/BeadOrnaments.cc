/*
  http://www.matrix67.com/blog/archives/682
  http://hackerrank.tumblr.com/post/42595035698/bead-ornaments-challenge

  The number of spanning trees of a complete graph is n^(n-2) Then among the n
  colors, try find n-1 edges. But for each edge (a, b), there are Na * Nb ways
  of connection.


*/
#include "cassert"
#include "iostream"
#include "algorithm"
#include "vector"

const int MOD = 1000000007;

int bitcount(int mask) {
  int cnt = 0;
  while(mask > 0) {
    mask &= mask-1;
    ++cnt;
  }
  return cnt;
}

long long pow(int a, int n) {
  if (n < 0) {
    return pow(pow(a, MOD - 2), -n);
  }
  if (n == 0) {
    return 1;
  }
  if (n == 1) {
    return a;
  }
  long long res = pow(a, n/2);
  res = res * res % MOD;
  if (n & 1) {
    res = res * a % MOD;
  }
  return res;
}

long long total_ways_dp(const std::vector<int>& beads) {
  int n = beads.size(), ALL = (1<<n) - 1;
  std::vector<int> beads_sum(1<<n);
  std::vector<long long> ways(1<<n);
  // 
  // dp[mask] = sum{dp[submask_a] * dp[submask_b] * beads[mask_a] * beads[mask_b]}
  for (int mask = 1; mask <= ALL; ++mask) {
    int k = 0, m = bitcount(mask), submask = (mask-1)&mask;
    while(k < n && (mask&(1<<k)) == 0) {
      ++ k;
    }
    beads_sum[mask] = beads_sum[submask] + beads[k];
    // only consider the last node!
    if (m == 1) {  // single node
      ways[mask] = pow(beads[k], beads[k] - 2);
    } else {
      for (int mask_a = (mask-1)&mask, mask_b; mask_a > 0; mask_a = (mask_a-1) & mask) {
	mask_b = mask - mask_a;
	ways[mask] = (ways[mask] + ways[mask_a] * ways[mask_b] % MOD * beads_sum[mask_a] * beads_sum[mask_b]) % MOD;
      }
      // overcount
      // ways[mask] /= 2(m-1);
      ways[mask] = ways[mask] * pow(2*(m-1), MOD-2) % MOD;
    }
  }
  return ways[ALL];
}

int main() {
  int T, n;
  for (std::cin >> T; T-- && std::cin >> n; ) {
    std::vector<int> beads(n);
    for (auto& e : beads) {
      std::cin >> e;
    }
    std::cout << total_ways_dp(beads) << std::endl;
  }
  return 0;
}
