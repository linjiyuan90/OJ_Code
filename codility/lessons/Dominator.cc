#include "algorithm"

// A nice code
// http://rafal.io/posts/codility-equi-leader.html
int solution(const vector<int> &A) {
  if (A.empty()) {
    return -1;
  }
  // there is at most 1 dominator
  int dominator = A[0];
  int cnt = 0;
  for (auto& x : A) {
    if (x == dominator) {
      ++ cnt;
    } else if (--cnt == 0) {
      dominator = x;
      cnt = 1;
    }
  }
  if (std::count(A.begin(), A.end(), dominator) <= A.size() / 2) {
    return - 1;
  }
  return std::find(A.begin(), A.end(), dominator) - A.begin();
}
