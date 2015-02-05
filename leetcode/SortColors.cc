class Solution {
public:
  void sortColors(int A[], int n) {
    for (int i = 0, l = 0, r = n; i < r;) {
      if (A[i] < 1) {
	std::swap(A[i++], A[l++]);
      } else if (A[i] > 1) {
	std::swap(A[i], A[--r]);
      } else {
	++i;
      }
    }
  }
};
