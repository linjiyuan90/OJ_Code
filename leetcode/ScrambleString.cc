class Solution {
public:
  bool isScramble(string s1, string s2) {
    if (s1.size() != s2.size()) {
      return false;
    }
    if (s1 == s2) {
      return true;
    }
    std::reverse(s1.begin(), s1.end());
    if (s1 == s2) {
      return true;
    }
    std::reverse(s1.begin(), s1.end());
    std::string ss1 = s1, ss2 = s2;
    std::sort(ss1.begin(), ss1.end());
    std::sort(ss2.begin(), ss2.end());
    if (ss1 != ss2) {
      return false;
    }
    for (int i = 1, n = s1.size(); i < n; ++i) {
      if ((isScramble(s1.substr(0, i), s2.substr(0, i)) 
	   && isScramble(s1.substr(i), s2.substr(i)))
	  || (isScramble(s1.substr(0, i), s2.substr(n - i, i)) 
	      && isScramble(s1.substr(i), s2.substr(0, n - i)))) {
	return true;
      }            
    }
    return false;
  }
};
