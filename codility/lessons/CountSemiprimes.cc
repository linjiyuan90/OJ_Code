#include "algorithm"

vector<int> solution(int N, vector<int> &P, vector<int> &Q) {
  // preprocess first
  std::vector<int> mark(N+1);
  for (int i = 1, x, j; i <= N; ++i) {
    int p = 0;
    for (j = 2, x = i; p < 2 && j <= x/j; ++j) {
      while (p < 2 && x % j == 0) {
	x /= j;
	++ p;
      }
    }
    if (x > 1) {
      ++ p;
    }
    mark[i] = (p == 2);
  }
  std::partial_sum(mark.begin(), mark.end(), mark.begin());
  std::vector<int> res;
  for (int i = 0, m = P.size(); i < m; ++i) {
    res.push_back(mark[Q[i]] - mark[P[i]-1]);
  }
  return res;
}
