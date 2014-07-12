#include "set"

int solution(vector<int> &A, vector<int> &B, vector<int> &C) {
  std::set<int> nails;
  int n = A.size(), m = C.size();
  int used = 0;
  for (int i = 0; i < n; ++i) {
    auto it = nails.lower_bound(A[i]);
    if (it == nails.end() || *it > B[i]) {
      while (used < m && !(A[i] <= C[used] && C[used] <= B[i])) {
	nails.insert(C[used++]);
      }
      if (used == m) {
	return -1;
      }
      nails.insert(C[used++]);
    }
  }
  return used;
}
