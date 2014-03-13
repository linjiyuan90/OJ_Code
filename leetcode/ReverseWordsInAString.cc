
class Solution {
public:
  // need to compress spaces, trim
  void reverseWords(std::string &s) {
    std::reverse(s.begin(), s.end());
    int n = s.size();
    // find space
    for (int last = 0, ix = 0, jx = 0; ix <= n; ++ix) {
      if (ix == n) {
	std::reverse(s.begin() + last, s.begin() + jx);
	s.resize(jx);
	break;
      }
      if (!::isspace(s[ix])) {
	if (jx > 0 && ix > 0 && ::isspace(s[ix-1])) {
	  std::reverse(s.begin() + last, s.begin() + jx);
	  s[jx++] = ' ';
	  last = jx;
	}
	s[jx++] = s[ix];
      }
    }
  }
};
