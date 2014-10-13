/*
  Distributed Join between 2 clusters A, B.
  That's, for each a[i], join with all b[j]
  Find the minimal copy to finish the join.
  For example, copy all b[j] to a[0], then copy all a[1..] to a[0] to join
  
  Sort A, B, assume A.back() > B.back()
  Firstly, copy all B to A.back(), this is a must operation.
  Then for each A[i], choose min(A[i], B.sum())
*/

#include "numeric"
#include "iostream"
#include "algorithm"
#include "vector"
#include "functional"

std::istream& operator>>(std::istream& in, std::vector<int>& vt) {
  for (auto& x : vt) {
    in >> x;
  }
  return in;
}

int64_t minCopy(std::vector<int>& a, std::vector<int>& b) {
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  if (a.back() < b.back()) {
    a.swap(b);
  }
  int64_t bSum = std::accumulate(b.begin(), b.end(), 0ll);
  int64_t ans = bSum;
  for (int i = 0, n = a.size(); i < n - 1; ++i) {
    ans += std::min(bSum, static_cast<int64_t>(a[i]));
  }
  return ans;
}

int main() {
  for (int n, m; std::cin >> n >> m; ) {
    std::vector<int> a(n), b(m);
    std::cin >> a >> b;
    std::cout << minCopy(a, b) << std::endl;
  }
  return 0;
}
