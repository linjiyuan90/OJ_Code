class Solution {
public:
  std::vector<int> searchRange(int A[], int n, int target) {
    int left = lower_bound(A, n, target);
    if (left == n || A[left] != target) {
      return std::vector<int>{-1, -1};
    }
    int right = lower_bound(A, n, target+1);
    return std::vector<int> {left, right - 1};
  }
  
private:
  int lower_bound(int A[], int n, int target) {
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
