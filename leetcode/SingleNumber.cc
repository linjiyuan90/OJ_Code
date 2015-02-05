class Solution {
public:
  int singleNumber(int A[], int n) {
    int ans = 0;
    for_each(A, A + n, [&ans](int x){ans ^= x;});
    return ans;
  }
};
