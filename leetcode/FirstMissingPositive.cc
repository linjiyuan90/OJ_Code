class Solution {
public:
  // Very interesting solution
  // https://github.com/Dionysus1227/edocteel/blob/master/First%20Missing%20Positive.cc
  int firstMissingPositive(int A[], int n) {
    // swap to make 1 to A[0], 2 to A[1] ...
    for (int i = 0; i < n; ++i) {
      // While the target value doesn't satisfy the requirement?
      for (; 1 <= A[i] && A[i] <= n && A[i] != A[A[i] - 1]; ) {
	std::swap(A[A[i] - 1], A[i]);
      }
    }
    int ans = 1;
    while (ans <= n && A[ans - 1] == ans) {
      ++ ans;
    }
    return ans;
  }
};

// [1, 1]
