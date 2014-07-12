/*
  For each elements e in A, count number of elements in A that is not a divisor of e.
  
  Note the condition that values are in [1, 2n]
  And ln(n+1) < 1 + 1/2 + 1/3 ... + 1/n < ln(n)+1
  O(nlogn)
*/

#include "map"

vector<int> solution(vector<int>& A) {
  // calculate the factors brute forcely
  std::map<int, int> cnt;
  for (auto& e : A) {
    ++ cnt[e];
  }
  int n = A.size();
  std::vector<int> factor_cnts(2*n + 1);
  for (int i = 1; i <= 2*n; ++i) {
    if (cnt[i] > 0) {
      for (int j = 1; i*j <= 2*n; ++j) {
	factor_cnts[i*j] += cnt[i];
      }
    }
  }
  std::vector<int> res;
  for (auto& e : A) {
    res.push_back(n - factor_cnts[e]);
  }
  return res;
}
