#include "string"
#include "algorithm"
#include "iostream"
#include "unordered_map"

class Solution {
public:
  std::string minWindow(std::string S, std::string T) {
    std::string ans = "";
    std::unordered_map<char, int> cnt;
    for (auto c : T) {
      cnt[c] -= 1;
    }
    int have = 0, num = T.length();
    for (int i = 0, j = 0, n = S.length(); i < n || j < n; ) {
      if (j < n && have < num) {
	if (cnt.count(S[j]) && cnt[S[j]]++ < 0) {
	  ++ have;
	}
	++ j;
      } else {
	if (cnt.count(S[i]) && cnt[S[i]]-- <= 0) {
	  -- have;
	}
	++ i;
      }
      if (have >= num) {
	if (ans == "" || ans.length() > j - i) {
	  ans = S.substr(i, j - i);
	}
      }
    }
    return ans;
  }
};


int main() {
  Solution sol;
  std::cout << sol.minWindow("bba", "ab") << std::endl;
  std::cout << sol.minWindow("aa", "aa") << std::endl;
  return 0;
}
