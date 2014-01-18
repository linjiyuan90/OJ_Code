class Solution {
public:
  int removeDuplicates(int A[], int n) {
    int ans = 0;
    for (size_t ix = 0; ix < n; ix ++) {
      if (ix == 0 || A[ix] != A[ix-1]) {
	A[ans ++] = A[ix];
      }
    }
    return ans;
  }
};
