/*
  DP is incorrect!!!  
  A = a + b, then merge solution(a) and solution(b). There maybe that a
  suboptimal solution of a combines another suboptimal solution of b is better
  than solution(a) + solution(b).
  For example, 77 = [1, 2, 4, 5, 9, 18, 36, 41, 77] while a dp approach gives 10.


  
*/

#include "algorithm"
#include "vector"

const int MAXN = 600;

std::vector<int> pre(MAXN + 1);
std::vector<int> chain[MAXN + 1];

int (int A) {
  if (pre[A] != 0) {
    return pre[A];
  }
  if (A == 1) {
    return 1;
  }
  
  for (int a = (A+1)/2; a < A; ++a) {
    int gt = solution(a);
    int lt = solution(A - a);
    if (pre[A] == 0 || chain[A].size() > try_chain.size()) {
      pre[A] = a;
      chain[A] = try_chain;
    }
  }
  return pre[A];
}

std::vector<int> solution(int A) {
}
