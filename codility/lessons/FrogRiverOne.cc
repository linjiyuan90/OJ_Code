/*
  Find the earliest time when a frog can jump to the other side of a river.
*/
int solution(int X, vector<int> &A) {
  // write your code in C++11
  int need = X;
  for (std::size_t i = 0, n = A.size(); i < n; ++i) {
    // reusing the same variables
    int l = A[i] <= X ? A[i] : A[i] - X;
    if (A[l - 1] <= X) {
      if (--need == 0) {
	return i;
      }
      A[l - 1] += X;
    }
  }
  return -1;
}
