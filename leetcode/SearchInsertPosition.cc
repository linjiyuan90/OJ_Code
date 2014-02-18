class Solution {
public:
    int searchInsert(int A[], int n, int target) {
      // cheat
      // return std::lower_bound(A, A + n, target) - A;
      int lo = 0, hi = n;
      while (lo < hi) {
	int mi = (lo + hi) / 2;
	if (A[mi] < target) {
	  lo = mi + 1;
	} else {
	  hi = mi;
	}
      }
      return lo;
    }
};
