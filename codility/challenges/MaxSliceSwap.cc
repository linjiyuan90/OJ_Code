/*
  Find the maximum sum of a compact subsequence of array elements after
  performing a single swap operation.

  It's wrong to combine maximum sum and one max value, since the maximum sum may
  not be the right sequence. It may erase some sequence.

  1) right side maxsum start at i, max_sum[i]
  2) left side max value dp[i] which consist of one element in {A[0..j]} and a tail A[j..i]
     dp[i] contains at least one element:
     a. max{A[0..i]}
     b. max{A[0..j]} + A[j..i]  (with a tail)

  the result will be: dp[i-1] + max_sum[i] - A[i]
*/

#include "algorithm"

int max_sum_with_left_swap(std::vector<int>& A) {
  int n = A.size();
  std::vector<int> dp(n);
  dp[0] = A[0];
  for (int i = 1, max = A[0]; i < n; ++i) {
    max = std::max(max, A[i]);
    dp[i] = std::max(dp[i-1] + A[i], max);
  }
  std::vector<int> max_sum(n);
  for (int i = n - 1, sum = 0; i >= 0; --i) {
    max_sum[i] = sum + A[i];
    sum = std::max(0, sum + A[i]);
  }
  int res = max_sum[0];
  for (int i = 1; i < n; ++i) {
    res = std::max(res, max_sum[i]);
    res = std::max(res, dp[i-1] - A[i] + max_sum[i]);
  }
  return res;
}

int solution(vector<int> &A) {
  int res = max_sum_with_left_swap(A);
  std::reverse(A.begin(), A.end());
  return std::max(res, max_sum_with_left_swap(A));
}
