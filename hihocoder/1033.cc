/*
 Define f(x) = a0 - a1 + a2 - a3 ..., where x = a0a2a2..., its digit representation.
 Given 0<= l, r <= 10^18, |k| <= 100, calculate the sum of x, where f(x) = k
 
 Define, num[len][k], sum[len][k] be the num/sum of that f(x) = k where x has exactly len digits (may have preceeding zero!!!)
 num[len][k] = ∑∑num[l][sign(len-l)*(d-k)], 1 <= l < len, d = 0..9
 sum[len][k] = ∑∑d*num[l][sign(len-l)*(d-k)] + sum[l][sign(len-l)*(d-k)], 1 <= l < len, d = 0..9
 sign(v) = v % 2 == 1 ? 1 : -1
 
 Define g(v) be the sum of x where f(x) = k and 0 <= x < v
 
 The answer will be g(r+1) - g(l)
 */
#include "iostream"
#include "vector"
#include "algorithm"
#include "string"
#include "cmath"
#include "cstdio"

namespace AlternativeSum {
  
  const int Mod = 1000000007;
  const int MaxLen = 18;
  const int MaxK = 100;
  const int Offset = MaxK;
  
  std::vector<int> pow10(MaxLen + 1);
  std::vector<std::vector<int> > num(MaxLen + 1, std::vector<int>(2*MaxK + 1));
  std::vector<std::vector<int> > sum(MaxLen + 1, std::vector<int>(2*MaxK + 1));
  
  std::string to_string(long long v) {
    char buf[20];
    sprintf(buf, "%lld", v);
    return buf;
  }
  
  void init() {
    pow10[0] = 1;
    for (int i = 1; i <= MaxLen; ++i) {
      pow10[i] = pow10[i-1] * 10ll % Mod;
    }
    num[0][Offset] = 1;
    for (int d = 0; d <= 9; ++d) {
      num[1][Offset + d] = 1;
      sum[1][Offset + d] = d;
    }
    for (int len = 2; len <= MaxLen; ++len) {
      for (int k = -MaxK; k <= MaxK; ++k) {
        for (int d = 0; d <= 9; ++d) {
          if (::abs(d-k) > MaxK) {
            continue;
          }
          int lenK = Offset + k;
          int lK = Offset + d-k;
          num[len][lenK] = (num[len][lenK] + num[len-1][lK]) % Mod;
          sum[len][lenK] = (sum[len][lenK] +
                            sum[len-1][lK] + 1ll * d * pow10[len-1] * num[len-1][lK] % Mod) % Mod;
        }
      }
    }
  }
  
  int accumulateSum(long long v, int k) {
    int ans = 0;
    const std::string& vStr = to_string(v);
    for (int i = 0, n = vStr.size(), sign = 1, sd = 0, nsd = 0; i < n; ++i, sign = -sign) {
      int d = vStr[i] - '0';
      int l = n - i - 1;
      for (int di = 0; di < d; ++di) {
        if (i == 0 && di == 0) {
          // prevent leading 0
          for (int len = n-1; len > 0; --len) {
            for (int ldi = 1; ldi <= 9; ++ldi) {
              if (::abs(ldi - k) > MaxK) {
                continue;
              }
              ans = (ans + 1ll * ldi * pow10[len-1] * num[len-1][Offset + ldi-k] % Mod + sum[len-1][Offset + ldi-k]) % Mod;
            }
          }
          continue;
        }
        int sdi = sd + sign * di;
        if (::abs(sdi - k) > MaxK) {
          continue;
        }
        int nsdi = (nsd + 1ll * di * pow10[l] % Mod) % Mod;
        int lK = Offset + sign * (sdi - k);
        ans = (ans + 1ll * nsdi * num[l][lK] % Mod + sum[l][lK]) % Mod;
      }
      sd += sign * d;
      nsd = (nsd + 1ll * d * pow10[l] % Mod) % Mod;
    }
    return ans;
  }
  /*
  void test() {
    for (int k = -MaxK; k <= MaxK; ++k) {
      int sum = 0;
      for (int n = 0; n <= 2000; ++n) {
        if (sum != accumulateSum(n, k)) {
          std::cout << n << " " << k << " " << sum << " " << accumulateSum(n, k) << std::endl;
          exit(1);
        }
        int nk = 0, sign = 1;
        for (const auto& ch : std::to_string(n)) {
          nk = nk + sign * (ch - '0');
          sign = -sign;
        }
        if (nk == k) {
          sum = (sum + n) % Mod;
        }
      }
    }
  }*/
}

int main() {
  using namespace AlternativeSum;
  init();
  // test();
  for (long long l, r, k; std::cin >> l >> r >> k; ) {
    std::cout << (accumulateSum(r + 1, k) - accumulateSum(l, k) + Mod) % Mod << std::endl;
  }
  return 0;
}
