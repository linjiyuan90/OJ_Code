class Solution {
public:
  void merge(int A[], int m, int B[], int n) {
    for (int ai = m-1; ai >= 0; --ai) {
      A[ai+n] = A[ai];
    }
    for (int i = n, j = 0, k = 0; i < n+m || j < n; ) {
      if (i == n+m || j < n && A[i] > B[j]) {
	A[k++] = B[j++];
      } else {
	A[k++] = A[i++];
      }
    }
  }
};
