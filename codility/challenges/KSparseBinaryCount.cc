/*
  How many number in [A, B] that its 1s in its binary representation has gap >= K.
  
  Thanks to the general framework:  https://code.google.com/codejam/contest/2994486/dashboard#s=a&a=1
  
*/

#include "unordered_map"
#include "functional"
#include "algorithm"

template<typename A, typename B>
class PairHash {
  std::hash<A> aHash;
  std::hash<B> bHash;
public:
  std::size_t operator() (const std::pair<A, B>& p) const {
    return aHash(p.first) ^ bHash(p.second);
  }
};

class KSparse {
  const int MOD = 1000000007;

  // using unordered_map will TLE for the largest case
  // std::unordered_map<std::pair<int, bool>, int, PairHash<int, bool>> cache;
  int cache[2][300010];
  
  int count(int i, bool less, const std::string& str, int k) {
    if (i >= str.length()) {
      return less;
    }
    if (cache[less][i] != -1) {
      return cache[less][i];
    }
    /*
      if (cache.count({i, less})) {
      return cache[{i, less}];
      }
      int& ans = cache[{i, less}];
    */
    int& ans = cache[less][i];
    ans = 0;
    bool next = less || str[i] == '1';
    // add 0 here
    ans += count(i+1, next, str, k);
    // add 1 here
    if (next) {
      for (std::size_t j = i+1; j < i+k+1 && j < str.length(); ++j) {
        less = less || str[j] == '1';
      }
      ans += count(i+k+1, less, str, k);
    }
    return ans %= MOD;
  }
public:
  int count(const std::string& str, int k) {
    // cache.clear();
    int n = str.length();
    std::fill(cache[0], cache[0] + n + 1, -1);
    std::fill(cache[1], cache[1] + n + 1, -1);
    return count(0, false, str, k);
  }
  
  void incOne(std::string& str) {
    std::reverse(str.begin(), str.end());
    int c = 1;
    for (std::size_t i = 0, n = str.size(); i < n && c > 0; ++i) {
      ++str[i];
      c = 0;
      if (str[i] == '2') {
        c = 1;
        str[i] = '0';
      }
    }
    if (c > 0) {
      str.push_back('1');
    }
    std::reverse(str.begin(), str.end());
  }

  int count(std::string S, std::string T, int K) {
    // inc T first;
    incOne(T);
    return (0ll + MOD + count(T, K) - count(S, K)) % MOD;
  }
};

int solution(string &S, string &T, int K) {
  KSparse ksparse;
  return ksparse.count(S, T, K);
}
