class Solution {
  double findMedianSortedArrays(int A[], int n, int B[], int m, int k) {
    if (k <= 0 || k > n + m) {
      throw std::invalid_argument("k should be: 1 <= k <= n + m");
    }
    if (n == 0) {
      return B[k - 1];
    }
    if (m == 0) {
      return A[k - 1];
    }
    if (k == 1) {
      return std::min(A[0], B[0]);
    }
    if (k == n + m) {
      return std::max(A[n-1], B[m-1]);
    }
    int a = std::min(k / 2, n);
    int b = k - a;
    if (b > m) {
      b = m;
      a = k - b;
    }
    if (A[a-1] < B[b-1]) {
      return findMedianSortedArrays(A + a, n - a, B, m, k - a);
    } else {
      return findMedianSortedArrays(A, n, B + b, m - b, k - b);
    }
  }
public:
  double findMedianSortedArrays(int A[], int n, int B[], int m) {
    if ((n + m) % 2 == 0) {
      return (findMedianSortedArrays(A, n, B, m, (n+m)/2) + 
	      findMedianSortedArrays(A, n, B, m, (n+m)/2+1)) / 2.0;
    } else {
      return findMedianSortedArrays(A, n, B, m, (n+m+1)/2);
    }
  }
};
