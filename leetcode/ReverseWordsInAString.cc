class Solution {
public:
  void reverseWords(string &s) {
    // compress spaces
    size_t n = 0;
    for (size_t i = 0; i < s.size(); ++i) {
      if (::isspace(s[i]) 
	  && (n == 0 || ::isspace(s[n-1]))) {
	continue;
      } else {
	s[n++] = s[i];
      }
    }
    if (n > 0 && ::isspace(s[n-1])) {
      -- n;
    }
    s.resize(n);
    // reverse words
    std::reverse(s.begin(), s.end());
    size_t l = 0;
    for (size_t i = 0; i < n; ++i) {
      if (::isspace(s[i])) {
	std::reverse(s.begin() + l, s.begin() + i);
	l = i + 1;
      }
    }
    std::reverse(s.begin() + l, s.end());
  }
};
