/*
  Native KMP.
*/
#include "iostream"
#include "string"
#include "vector"

std::vector<int> getNext(const std::string& str) {
  std::vector<int> next(str.size());
  if (!str.empty()) {
    next[0] = -1;
    for (int i = 1, n = str.size(); i < n; ++i) {
      for (next[i] = next[i-1] + 1; next[i] != -1 && str[next[i]] != str[i]; ) {
        next[i] = next[i] == 0 ? -1 : next[next[i]-1] + 1;
      }
    }
  }
  return next;
}

// how many times A occurs in B
int occurrence(const std::string& A, const std::string& B) {
  std::vector<int> next = getNext(A);
  int n = A.size(), m = B.size(), c = 0;
  for (int i = 0, j = 0; j < m; ) {
    if (A[i] == B[j]) {
      ++i;
      ++j;
      if (i == n) {
        ++c;
        i = next[i-1] + 1;
      }
    } else {
      if (i == 0) {
        ++j;
      } else {
        i = next[i-1] + 1;
      }
    }
  }
  return c;
}

int main() {
  int T;
  std::string A, B;
  for (std::cin >> T; T--; ) {
    std::cin >> A >> B;
    std::cout << occurrence(A, B) << std::endl;
  }
  return 0;
}
