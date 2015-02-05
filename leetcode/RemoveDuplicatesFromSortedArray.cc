class Solution {
public:
  int removeDuplicates(int A[], int n) {
    int m = 0;
    for (int i = 0; i < n; ++i) {
      if (m < 1 || A[m-1] != A[i]) {
        A[m++] = A[i];
      }
    }
    return m;
  }
};
