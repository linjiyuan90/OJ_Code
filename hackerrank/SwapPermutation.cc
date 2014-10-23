/*
  Given an array A = [1, 2, ..., n]
  How many sequence can get after exactly k adjacent swaps on A?
  How many sequence can get after at most k swaps on A?
  
  let dp[n][k] be the number of sequence can get after exactly k adjacent swaps with 
  restriction that no "come back" swap is performed (swap(a, b) and swap(b, a)).
  Then dp[n][k] = ∑dp[n-1][k'], k-(n-1) <= k' <= k
  That's to enumerate a[n]'s final position (n possible positions), and only
  swap a[n] with others.
  Base on the assumption that the swap sequences is equal to a swap sequences that 
  is sorted by max(a, b) (where a, b means the number to be swaped in swap(a, b))?
  The answer is: ∑dp[n][k-2j], 0 <= 2j <= k


  https://www.hackerrank.com/challenges/swappermutation/editorial
  With respect to problem 2,
  dp[n][k] = dp[n-1][k] + (n-1)*dp[n-1][k-1]
  append the end or swap with one of a[1..n-1]
  The answer is: ∑dp[n][ki], 0 <= ki <= k
*/

#include "iostream"
#include "vector"
#include "numeric"

const int Mod = 1000000007;
const int MaxN = 2500;
const int MaxK = 2500;

std::vector<std::vector<int>> initAdjacentSwapWays() {
  std::vector<std::vector<int>> dp(MaxN + 1, std::vector<int>(MaxK + 1));
  dp[1][0] = 1;
  for (int n = 2; n <= MaxN; ++n) {
    int sum = 0;
    for (int k = 0; k <= MaxK; ++k) {
      // add dp[n-1][k'], k' = k
      sum = (sum + dp[n-1][k]) % Mod;
      dp[n][k] = sum;
      // erase dp[n-1][k'], k' = k-(n-1)
      if (k-(n-1) >= 0) {
        sum = (sum - dp[n-1][k-(n-1)] + Mod) % Mod;
      }
    }
  }
  for (int n = 2; n <= MaxN; ++n) {
    for (int k = 2; k <= MaxK; ++k) {
      dp[n][k] = (dp[n][k] + dp[n][k-2]) % Mod;
    }
  }
  return dp;
}

std::vector<std::vector<int>> initSwapWays() {
  std::vector<std::vector<int>> dp(MaxN + 1, std::vector<int>(MaxK + 1));
  dp[0][0] = 1;
  for (int n = 1; n <= MaxN; ++n) {
    for (int k = 0; k <= MaxK; ++k) {
      dp[n][k] = (dp[n-1][k] + 1ll * (n-1) * dp[n-1][k-1] % Mod) % Mod;
    }
  }
  for (int n = 1; n <= MaxN; ++n) {
    for (int k = 1; k <= MaxK; ++k) {
      dp[n][k] = (dp[n][k] + dp[n][k-1]) % Mod;
    }
  }
  return dp;
}

int main() {
  auto adjacentWays = initAdjacentSwapWays();
  auto swapWays = initSwapWays();
  for (int n, k; std::cin >> n >> k; ) {
    std::cout << adjacentWays[n][k] << " " << swapWays[n][k] << std::endl;
  }
  return 0;
}
