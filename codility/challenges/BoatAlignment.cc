// A binary search is obvious.
// How to design O(n)?

bool check(std::vector<int>& R, int X, int M, int l) {
  int last = 0;
  for (auto& r : R) {
    if (last > r + l - X) {
      return false;
    }
    // left boat side: [r - l - X, r + l - X]
    last = std::max(r - l - X, last) + 2*X;
  }
  return last <= M;
}

int solution(std::vector<int>& R, int X, int M) {
  int low = 0, high = M + 1;
  while (low < high) {
    int mid = (low + high) / 2;
    if (check(R, X, M, mid)) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return high > M ? -1 : high;
}
