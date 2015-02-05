class Solution {
    
  int lower_bound(int A[], int n, int target) {
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
    
  int upper_bound(int A[], int n, int target) {
    int lo = 0, hi = n;
    while (lo < hi) {
      int mi = (lo + hi) / 2;
      if (A[mi] > target) {
        hi = mi;
      } else {
        lo = mi + 1;
      }
    }
    return lo;
  }
    
public:
  vector<int> searchRange(int A[], int n, int target) {
    int l = lower_bound(A, n, target);
    int r = upper_bound(A, n, target);
    return l == r ? vector<int>{-1, -1} :  vector<int>{l, r - 1};
  }
};
