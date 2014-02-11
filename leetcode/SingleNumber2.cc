class Solution {
public:
  // It seems that the single number appears once.
  // Count every digit, module it with 3
  int singleNumber(int A[], int n) {
    std::vector<int> count(32);
    for (int i = 0; i < n; ++i) {
      for (int d = 0; d < 32; ++d) {
	count[d] += (A[i] >> d) & 1;
      }
    }
    int ans = 0;
    for (int d = 0; d < 32; ++d) {
      // assert(count[d] % 3 == 0 || count[d] % 3 == 1);
      ans |= (count[d] % 3) << d;
    }
    return ans;
  }
};
