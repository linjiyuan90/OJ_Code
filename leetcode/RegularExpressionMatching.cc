class Solution {
public:
  bool isMatch(const char *s, const char *p) {
    if (*s == 0 && *p == 0) {
      return true;
    }
    if (*s != 0 && *p == 0) {  // let *s == 0 be judged below
      return false;
    }
    const char *q = p + 1;
    while (*q == '*') {
      ++q;
    }
    if (q != p + 1) {  // '*'
      if (isMatch(s, q)) {
	return true;
      }
      while (*s != 0 && (*p == '.' || *s == *p)) {
	if (isMatch(++s, q)) {
	  return true;
	}
      }
    } else {
      return *s != 0 && (*p == '.' || *s == *p) && isMatch(s+1, q);
    }
    return false;
  }
};
