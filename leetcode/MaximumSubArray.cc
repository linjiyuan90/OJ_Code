class Solution {
public:
  int maxSubArray(int A[], int n) {
    int ans = A[0];
    for (int i = 0, sum = 0; i < n; ++i) {
      sum = std::max(sum + A[i], A[i]);
      ans = std::max(ans, sum);
    }
    return ans;
  }
};
