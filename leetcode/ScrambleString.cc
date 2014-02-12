class Solution {
public:
  bool isScramble(std::string s1, std::string s2) {
    std::string s1_sorted = s1, s2_sorted = s2;
    std::sort(s1_sorted.begin(), s1_sorted.end());
    std::sort(s2_sorted.begin(), s2_sorted.end());
    if (s1_sorted != s2_sorted) {  // crucial prune
      return false;
    }
    // same string are scramble string too
    if (s1 == s2) {
      return true;
    }
    std::reverse(s2.begin(), s2.end());
    if (s1 == s2) {
      return true;
    }
    std::reverse(s2.begin(), s2.end());
    int n = s1.length();
    for (size_t l = 1; l < n; ++l) {
      if (isScramble(s1.substr(0, l), s2.substr(0, l)) && 
	  isScramble(s1.substr(l), s2.substr(l)) ||
	  isScramble(s1.substr(0, l), s2.substr(n-l, l)) && 
	  isScramble(s1.substr(l), s2.substr(0, n-l))
	  ) {
	return true;
      }
    }
    return false;
  }
};


// Use memo?
// dp[i, j, len] means isScramble(s1.substr(i, len), s2.substr(j, len))
