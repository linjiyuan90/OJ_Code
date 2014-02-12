class Solution {
public:
  int divide(int dividend, int divisor) {
    // let k = dividend / divisor
    // Consider k's binary expression
    // Can't use shift, so solve it recursively.
    // note negative, INT_MAX
    int sign = (dividend > 0) ^ (divisor > 0) ? -1 : 1;
    long long l_dividend = abs((long long)dividend);
    long long l_divisor = abs((long long)divisor);
    return divide(l_dividend, l_divisor) * sign;
  }

private:
  // substract it
  long long divide(long long &dividend, long long divisor) {
    if (divisor > dividend) {
      return 0;
    }
    // try 2*divisor
    long long ans = divide(dividend, divisor + divisor);
    // need to double
    // maybe pass in paramter will be more clear
    ans += ans;
    if (dividend >= divisor) {
      ++ ans;
      dividend -= divisor;
    }
    return ans;
  }
};
