#include "algorithm"

vector<int> solution(vector<int> &A, vector<int> &B) {
  int L = *std::max_element(A.begin(), A.end());
  std::vector<int> dp(L + 1);
  dp[0] = 1;
  dp[1] = 1;
  for (int i = 2; i <= L; ++i) {
    dp[i] = dp[i-1] + dp[i-2];
  }
  std::vector<int> res(A.size());
  for (int i = 0, n = A.size(); i < n; ++i) {
    res[i] = dp[A[i]] % (1 << B[i]);
    if (res[i] < 0) {  // note dp may be negative!!!
      res[i] += 1 << B[i];
    }
  }
  return res;
}
