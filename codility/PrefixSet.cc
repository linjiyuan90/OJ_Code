#include "iostream"
#include "algorithm"
#include "vector"

bool ok[1000000];

int solution(const std::vector<int> &A) {
  int n = A.size();
  std::fill(ok, ok + n, false);
  for (std::vector<int>::const_iterator it = A.begin();
       it != A.end(); ++it) {
    ok[*it] = true;
  }
  int count = std::count(ok, ok + n, true);
  for (size_t ix = 0; ix < n; ++ix) {
    if (ok[A[ix]]) {
      ok[A[ix]] = false;
      if (--count == 0) {
	return ix;
      }
    }
  }
}
