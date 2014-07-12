#include "limits"

int solution(vector<int> &A) {
  const int MAX = std::numeric_limits<int>::max();
  A.push_back(1);
  int n = A.size();
  std::vector<int> dp(n, MAX);
  for (int i = 0; i < n; ++i) {
    if (A[i] == 1) {
      for (int a = 0, b = 1; i - b >= -1; std::swap(a, b), b += a) {
	if (i - b == -1) {
	  dp[i] = 1;
	  break;
	}
	if (A[i-b] == 1 && dp[i-b] != MAX) {
	  dp[i] = std::min(dp[i], dp[i-b] + 1);
	}
      }
    }
  }
  return dp.back() == MAX ? -1 : dp.back();
}
