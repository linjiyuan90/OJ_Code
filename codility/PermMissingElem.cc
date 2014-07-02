
int solution(vector<int> &A) {
  int n = A.size();
  for (int i = 0; i < n; ++i) {
    while(1 <= A[i] && A[i] <=n && A[A[i] - 1] != A[i]) {
      std::swap(A[A[i] - 1], A[i]);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (A[i] != i + 1) {
      return i + 1;
    }
  }
  return n + 1;
}
