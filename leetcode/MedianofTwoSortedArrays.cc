// recursively solution is more easier to write
class Solution {
public:
  double findMedianSortedArrays(int A[], int m, int B[], int n) {
    if ((m+n) % 2 == 0) {
      return (findMedian(A, m, B, n, (m+n)/2) + findMedian(A, m, B, n, (m+n)/2+1)) / 2.0;
    } else {
      return findMedian(A, m, B, n, (m+n)/2+1); 
    }
  }
  
private:
  int findMedian(int A[], int m, int B[], int n, int c) {
    if (m == 0) {
      return B[c-1];
    }
    if (n == 0) {
      return A[c-1];
    }
    if (m + n == c) {
      return std::max(A[m-1], B[n-1]);
    }
    if (c == 1) {  // note when c == 1
      return std::min(A[0], B[0]);
    }
    int a = std::min(c/2, m);
    int b = c - a;
    if (b > n) {
      b = n;
      a = c - b;
    }
    if (A[a-1] < B[b-1]) {
      return findMedian(A+a, m-a, B, n, c-a);
    } else {
      return findMedian(A, m, B+b, n-b, c-b);
    }
  }
};


class Solution {
public:

  int mymin(int A[], int m, int B[], int n, int a, int b) {
    if (a >= m || b < n && A[a] > B[b]) {
      return B[b];
    }
    return A[a];
  }
  
  double findMedianSortedArrays(int A[], int m, int B[], int n) {
    // suppose C = merge(A, B)
    // then (C[l]+C[r])/2 will be the answer
    int l = (n+m-1)/2, r = (n+m)/2;
    int ai = m-1, bi = n-1;
    while (ai >= 0 && bi >= 0 && ai + bi + 1 > l) {
      // still need to drop s highest number in merge(A[0..ai], B[0..bi]) 
      int s = ai + bi + 1 - l;
      int sa = min(ai+1, s/2), sb = s - sa;
      if (sb > bi+1) {
	sb = bi + 1;
	sa = s - sb;
      }
      if (s == 1) {  // note this
	sa = sb = 1;
      }
      // sa > 0, sb > 0
      // after compare
      // maybe drop last sa number in A[0..ai]
      // maybe drop last sb number in B[0..bi]
      // where sa + sb = s
      if (A[ai-sa+1] > B[bi-sb+1]) {
	ai -= sa;
      } else {
	bi -= sb;
      }
    }
    double dl, dr;
    if (ai == -1) {
      dl = B[bi = l];
    } else if (bi == -1) {
      dl = A[ai = l];
    } else {
      // now we have that A[0..ai], B[0..bi] are the l+1 smallest numbers
      dl = max(A[ai], B[bi]);
    }
    dr = l == r ? dl : mymin(A, m, B, n, ai+1, bi+1);
    return (dl+dr)/2;
  }
  // test case
  // [1 1 3 3]
  // [1 1 3 3]
  // => 2
};

