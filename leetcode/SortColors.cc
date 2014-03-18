class Solution {
public:
  void sortColors(int A[], int n) {
    // quicksort partition
    int p = 1;
    for (int i = 0, j = 0, k = n; j < k;) {
      if (A[j] > p) {
	std::swap(A[j], A[--k]);
      } else if (A[j] < p) {
	std::swap(A[j++], A[i++]);
      } else {
	j++;
      }
    }
  }
};