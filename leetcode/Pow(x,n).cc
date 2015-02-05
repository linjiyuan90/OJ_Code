class Solution {
public:
  double pow(double x, int n) {
    // note when n < 0!!!
    // note when n = 2147483648!!!
    if (n < 0) {
      return pow(1.0 / x, -(1+n)) / x;
    }
    if (n == 0) {
      if (x == 0.0) {
	throw std::invalid_argument("Not scientific! 0.0 ^ 0");
      }
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
