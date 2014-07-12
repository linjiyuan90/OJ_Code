int solution(int M, vector<int> &A) {
  std::vector<int> cnt(M+1);
  int n = A.size();
  int res = 0;
  for (int i = 0, j = 0; i < n; ) {
    if (j < n && cnt[A[j]] == 0) {
      ++ cnt[A[j++]];
      res = std::min(res + j - i, 1000000000);
    } else {
      -- cnt[A[i++]];
    }
  }
  return res;
}
