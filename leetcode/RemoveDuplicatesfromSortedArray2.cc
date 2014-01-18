class Solution {
public:
  // remove elements that appear more than twice from a sorted array
  int removeDuplicates(int A[], int n) {
    int m = 0;
    for (int i = 0; i < n; ++i) {
      if (m < 2 ||
	  A[m-1] != A[i] ||
	  A[m-2] != A[i]) {
	A[m++] = A[i];
      }
    }
    return m;
  }
};
