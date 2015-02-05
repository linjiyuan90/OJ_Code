class Solution {
public:
  int searchInsert(int A[], int n, int target) {
    int lo = 0, hi = n;
    while (lo < hi) {
      int mi = (lo + hi) / 2;
      if (A[mi] >= target) {
        hi = mi;
      } else {
        lo = mi + 1;
      }
    }
    return lo;
  }
};
