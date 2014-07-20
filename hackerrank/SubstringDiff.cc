/*
  Seems an interestring problem!
  
  Find a longest length, that slice A[i, i+length-1] diffs B[j, j+length-1] <= K.

  For one dimension, finding a longest slice that statisfy some condition can be
  solved by two pointers.  With respect to this problem, first enumerate the
  offset, and comparing A[i...], B[i+off...] using two pointers.
  
  Note off can be negative.
*/

#include "iostream"
#include "string"
#include "vector"

int substring_diff(const std::string& A, const std::string& B, const int& K) {
  int n = A.size(), m = B.size();
  int res = 0;
  for (int off = -m; off < m; ++off) { // note when off < 0!!!
    for (int i = std::max(0, -off), j = i, d = 0; j < n && j+off < m; ) {
      d += (A[j] != B[j+off]);
      ++j;
      while (d > K) {
	d -= (A[i] != B[i+off]);
	++i;
      }
      res = std::max(res, j - i);
    }
  }
  return res;
}

int main() {
  int T, K;
  std::string A, B;
  for (std::cin >> T; T--; ) {
    std::cin >> K >> A >> B;
    std::cout << substring_diff(A, B, K) << std::endl;
  }
  return 0;	
}
