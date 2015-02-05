class Solution {
public:
  int removeDuplicates(int A[], int n) {
    int c = 0;
    for (int i = 0; i < n; ++i) {
      if (c < 2 || A[i] != A[c-1] || A[c-2] != A[c-1]) {
	A[c++] = A[i];
      }
    }
    return c;
  }
};
