#include "algorithm"

int solution(vector<int> &A) {
  std::sort(A.begin(), A.end());
  int res = ::abs(2 * A[0]);
  for (auto& e : A) {
    auto it = std::lower_bound(A.begin(), A.end(), -e);
    if (it != A.end()) {
      res = std::min(res, ::abs(e + *it));
    }
    if (it != A.begin()) {
      res = std::min(res, ::abs(e + *--it));
    }
  }
  return res;
}
