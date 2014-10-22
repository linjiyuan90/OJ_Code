/*
  Find the number of n-permutations with restriction that
  P[a[i]-1] > P[a[i]] < P[a[i]+1]
  P[b[i]-1] < P[b[i]] > P[b[i]+1]
  where a[], b[] is given
  n <= 5000
*/
#include "iostream"
#include "vector"
#include "algorithm"
#include "numeric"

const int Mod = 1000000007;

// dp[i, lt] be the number of ways that satisfying [1..i] and 
// there are lt remaining number that is less than P[i]. Of course,
// gt = n-i-lt
// dp[i, lt] = ∑dp[i-1, lt'], lt' > lt, if P[i-1] > P[i]
//             ∑dp[i-1, lt'], lt' <= lt, if P[i-1] < P[i]
//             ∑dp[i-1, lt'], if no restriction
//             0    if conflict

// interesting design :-)
// record how large current P[i] is

int main() {
  for (int N, K, L; std::cin >> N >> K >> L; ) {
    std::vector<int> a(K), b(L);
    for (auto& ai : a) {
      std::cin >> ai;
    }
    for (auto& bi : b) {
      std::cin >> bi;
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::vector<std::vector<int>> dp(N+1, std::vector<int>(N));
    for (int i = 1, ai = 0, bi = 0; i <= N; ++i) {
      if (i == 1) {
        std::fill(dp[1].begin(), dp[1].end(), 1);
      } else {
        bool gtRequire = (ai < a.size() && a[ai] == i) || (bi > 0 && b[bi-1] == i-1);
        bool ltRequire = (bi < b.size() && b[bi] == i) || (ai > 0 && a[ai-1] == i-1);
        if (ltRequire && gtRequire) {
          break;
        }
        if (ltRequire) {
          int sum = 0;
          for (int lt = 0; lt <= N - i; ++lt) {
            sum = (sum + dp[i-1][lt]) % Mod;
            dp[i][lt] = sum;
          }
        } else if (gtRequire) {
          int sum = dp[i-1][N-i+1];
          for (int lt = N-i; lt >= 0; --lt) {
            dp[i][lt] = sum;
            sum = (sum + dp[i-1][lt]) % Mod;
          }
        } else {
          int sum = std::accumulate(dp[i-1].begin(), dp[i-1].end(), 0ll) % Mod;
          // lt = [0, n-i]
          std::fill(dp[i].begin(), dp[i].begin() + (N-i) + 1, sum);
        }
        if (ai < a.size() && a[ai] == i) {
          ++ai;
        }
        if (bi < b.size() && b[bi] == i) {
          ++bi;
        }
      }
    }
    std::cout << dp[N][0] << std::endl;
  }
  return 0;
}
