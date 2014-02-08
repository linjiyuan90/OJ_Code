class Solution {
public:
  // the single one number appears once or appears not twice?
  int singleNumber(int A[], int n) {
    int all = 0;
    for (int i = 0; i < n; ++i) {
      all ^= A[i];
    }
    return all;
  }
};
