class Solution {
public:
  int search(int A[], int n, int target) {
    // first search the minimum element (the gap)
    int gap = search_gap(A, n);
    int *p = std::lower_bound(A, A + gap, target);
    if (p != A + gap && *p == target) {
      return p - A;
    }
    p = std::lower_bound(A + gap, A + n, target);
    if (p != A + n && *p == target) {
      return p - A;
    }
    return -1;
  }

private:
  int search_gap(int A[], int n) {
    int lo = 0, hi = n-1;
    while (lo < hi) {
      int m = (lo + hi) / 2;
      if (A[m] > A[hi]) {
	lo = m + 1;
      } else {
	hi = m;
      }
    }
    return lo;
  }
};
