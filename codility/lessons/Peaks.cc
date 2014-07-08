/*
  How an O(nloglogn) algorithm is designed?
*/

#include "algorithm"
 
bool check(const std::vector<int>& peaks, int n, int a) {
  int m = peaks.size();
  bool isOk = true;
  for (int i = 0, j = 0; i < n; i += a) {
    while (j < m && peaks[j] < i) {
      ++ j;
    }
    if (j == m || peaks[j] >= i + a) {
      isOk = false;
      break;
    }
  }
  return isOk;
}
 
int solution(vector<int> &A) {
  std::vector<int> peaks;
  int n = A.size();
  for (int i = 1; i + 1 < n; ++i) {
    if (A[i] > A[i-1] && A[i] > A[i+1]) {
      peaks.push_back(i);
    }
  }
  int res = 0;
  for (int a = 1; a <= n/a; ++a) {
    if (n % a != 0) {
      continue;
    }
    if (check(peaks, n, a)) {
      res = std::max(res, n / a);
    }
    if (check(peaks, n, n/a)) {
      res = std::max(res, a);
    }
  }
  return res;
}
