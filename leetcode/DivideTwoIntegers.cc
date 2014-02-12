class Solution {
public:
  int divide(int dividend, int divisor) {
    // let k = dividend / divisor
    // Consider k's binary expression
    
    // note negative
    // note INT_MAX
    int s = (dividend > 0) ^ sign(divisor > 0) ? -1 : 1;
    dividend = abs(dividend);
    divisor = abs(divisor);

    // Can I use shift?
    int n = 1, d = divisor;
    while (d < dividend) {
      d <<= 1;
      n <<= 1;
    }
    int k = 0;
    while (dividend > 0 && d > 0) {
      if (dividend >= d) {
	dividend -= d;
	k += n;
      }
      d >>= 1;
      n >>= 1;
    }
    return k * s;
  }

};


// like kuaisumi
