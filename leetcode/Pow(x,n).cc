class Solution {
public:
  double pow(double x, int n) {
    if (n < 0) {
      return (1/x)*pow(1/x, -(1+n)); // note INT_MIN
    }
    if (n == 0) {
      return 1.0;
    }
    if (n == 1) {
      return x;
    }
    double ans = pow(x, n / 2);
    ans *= ans;
    if (n & 1) {
      ans *= x;
    }
    return ans;
  }
};
