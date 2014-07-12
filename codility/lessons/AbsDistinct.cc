// note overflow

int solution(const vector<int> &A) {
  int res = 0;
  for (int i = 0, j = A.size() - 1; i <= j; ) {
    while (i + 1 <= j && ::llabs(A[i]) == ::llabs(A[i + 1])) {
      ++ i;
    }
    while (i <= j - 1 && ::llabs(A[j]) == ::llabs(A[j - 1])) {
      -- j;
    }
    if (::llabs(A[i]) < ::llabs(A[j])) {
      ++ res;
      -- j;
    } else if (::llabs(A[i]) == ::llabs(A[j])) {
      ++ res;
      ++ i;
      -- j;
    } else {
      ++ res;
      ++ i;
    }
  }
  return res;
}
