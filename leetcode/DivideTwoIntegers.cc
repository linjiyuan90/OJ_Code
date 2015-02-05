class Solution {
  // only use substract
  // while and substract is slow
  // need a log algorithm
  // note sign!
    
  int divideImpl(long long& dividend, long long divisor) {
    if (dividend < divisor) {
      return 0;
    }
    int res = divideImpl(dividend, divisor + divisor);
    res += res;
    if (dividend >= divisor) {
      dividend -= divisor;
      ++ res;
    }
    return res;
  }
  
  int divideImplIterative(long long dividend, long long divisor) {
    std::vector<long long> divisor2s(1, divisor);
    while (divisor2s.back() < dividend) {
      divisor2s.push_back(divisor2s.back() + divisor2s.back());
    }
    int res = 0;
    for (auto it = divisor2s.rbegin(); it != divisor2s.rend(); ++it) {
      res += res;
      if (dividend >= *it) {
        dividend -= *it;
        ++ res;
      }
    }
    return res;
  }
  
public:
  int divide(int dividend, int divisor) {
    int sign = ::signbit(dividend) ^ ::signbit(divisor);
    sign = sign == 1 ? -1 : 1;
    long long dividendLong = ::llabs(dividend);
    long long divisorLong = ::llabs(divisor);
    return sign * divideImplIterative(dividendLong, divisorLong);
  }
};
