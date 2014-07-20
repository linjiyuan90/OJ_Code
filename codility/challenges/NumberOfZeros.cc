/*
  Compute total number of zros in decimal representation of 1, ..., N
  
  Any generalizataion framework?
*/

#include "iostream"
#include "vector"

const long long Mod = 1410000017;

int solution(const string &S) {
  int L = S.length();
  std::vector<long long> num(L+1), tens(L+1);
  tens[0] = 1;
  for (int i = 1; i <= L; ++i) {
    num[i] = (num[i-1] + (S[L-i] - '0') * tens[i-1]) % Mod;
    tens[i] = tens[i-1] * 10 % Mod;
  }
  // number of zeros in [0, 99..9] and strings with fixed length, that's 10^l*l
  std::vector<long long> zeros(L+1), all_zeros(L+1);
  zeros[0] = 1;
  std::vector<long long> all_zeros(L+1);
  for (int l = 1; l <= L; ++l) {
    zeros[l] = (9 * all_zeros[l-1] + zeros[l-1]) % Mod;
    all_zeros[l] = l * tens[l-1] % Mod;
  }

  int l = L;
  long long ans = 0;
  for (auto& ch : S) {
    --l;
    int d = ch - '0';
    if (d > 0) {
      ans += (d-1) * all_zeros[l];
      ans += (l == L-1 ? zeros[l] : all_zeros[l] + tens[l]);
    } else {
      ans += num[l] + 1;
    }
    ans %= Mod;
  }
  return ans;
}
