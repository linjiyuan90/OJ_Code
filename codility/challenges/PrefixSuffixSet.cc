/*
  Given an array, count all pairs(P, Q) that satisfy {A[0], ... A[P]} == {A[S], .. A[N-1]}
  O(nlogn)
  At the begining of  each iteration, P, S is a PrefixSuffixSet.
  Then, try to expand P, S
  Once find a valid (P, S), try to find P', S' which A[P+1], ... A[P'] is in prefix[P], and
  A[S'], A[S'+1], ... A[S-1] is in suffix[S].
  Add (P' - P + 1) * (S - S' + 1) to res.
*/

#include "set"

int solution(vector<int> &A) {
  int n = A.size();
  int res = 0;
  std::set<int> prefix, suffix;
  std::set<int> prefix_need, suffix_need;
  for (int i = 0, j = n-1; i < n || j >= 0; ) {
    if (j < 0 || (i < n && prefix.size() < suffix.size())) {
      if (prefix.insert(A[i]).second) {
	prefix_need.erase(A[i]);
	if (!suffix.count(A[i])) {
	  suffix_need.insert(A[i]);
	}
      }
      ++ i;
    } else {
      if (suffix.insert(A[j]).second) {
	suffix_need.erase(A[j]);
	if (!prefix.count(A[j])) {
	  prefix_need.insert(A[j]);
	}
      }
      -- j;
    }
    // prefix suffix set
    if (prefix_need.empty() && suffix_need.empty()) {
      int ii = i, jj = j;
      while (ii < n && prefix.count(A[ii])) {
	++ ii;
      }
      while (jj >= 0 && suffix.count(A[jj])) {
	-- jj;
      }
      res += (ii - i + 1) * (j - jj + 1);
      i = ii;
      j = jj;
    }
  }
  return std::min(res, 1000000000);
}
