/*
  Find the shortest prefix that contains all the elements in A
*/

int solution(const vector<int> &A) {
  std::vector<bool> mark(A.size());
  int res = 0;
  for (int i = 0, n = A.size(); i < n; ++i) {
    if (!mark[A[i]]) {
      mark[A[i]] = true;
      res = i;
    }
  }
  return res;
}
