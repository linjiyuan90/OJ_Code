/*
  Find the only element which occures one times while others occcur three times.
  Like xor, but count each bit's occurrence % 3
*/

class Solution {
public:
  int singleNumber(int A[], int n) {
    // count each bit's occurrence % 3
    int one = 0, two = 0;
    for (int i = 0; i < n; ++i) {
      int common = A[i] & two;
      two -= common;
      two += one & (A[i] - common);
      one ^= A[i] - common;
    }
    return one;
  }
};
