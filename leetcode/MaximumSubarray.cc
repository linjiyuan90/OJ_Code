class Solution {
public:
  int maxSubArray(int A[], int n) {
    int ans = INT_MIN, prev = 0;
    for (int i = 0; i < n; ++i) {
      ans = std::max(ans, prev + A[i]);
      ans = std::max(ans, A[i]);
      prev = std::max(prev + A[i], A[i]);
    }
    return ans;
  }
};
