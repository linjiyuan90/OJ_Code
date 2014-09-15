/*
  Compute total number of zros in decimal representation of 1, ..., N
  
  Any generalizataion framework?
  https://code.google.com/codejam/contest/2994486/dashboard#s=a&a=1
  
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

namespace DigitCount {
  static std::unordered_map<int, std::pair<int, int>> cache[2];
  
  std::pair<int, int> countZero(int i, const std::string& S, bool lessA) {
    if (i == S.size()) {
      return {0, lessA};
    }
    if (cache[lessA].count(i)) {
      return cache[lessA][i];
    }
    auto& ans = cache[lessA][i];
    for (int x = 0; x <= S[i] - '0'; ++x) {
      auto res = countZero(i+1, S, lessA || x < S[i] - '0'); 
      int cnt = res.first;
      if (x == 0) {
        cnt += res.second;
      }
      ans.first = (ans.first + cnt) % Mod;
      ans.second = (ans.second + res.second) % Mod;
    }
    return ans;
  }

  std::string incOne(std::string S) {
    std::reverse(S.begin(), S.end());
    int c, i;
    for (c = 1, i = 0; c > 0 && i < S.size(); ++i) {
      c += S[i] - '0';
      S[i] = c % 10 + '0';
      c %= 10;
    }
    if (c > 0) {
      S.push_back('1');
    }
    std::reverse(S.begin(), S.end());
    return S;
  }
  
  int countZero(const std::string& S) {
    cache[0].clear();
    cache[1].clear();
    return countZero(0, incOne(S), false).first;
  }
}

int solution(const std::string& S) {
  return DigitCount::countZero(S);
}
