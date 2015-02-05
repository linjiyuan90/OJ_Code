class Solution {
public:
  // need to consider:
  // "a", ""
  // "a", "ab*"
  bool isMatch(const char *s, const char *p) {
    if (s == NULL && p == NULL) {
      return true;
    }
    if (s == NULL || p == NULL) {
      return false;
    }
    if (*p == 0) {
      return *s == 0;
    }
    // compress '*'
    const char* q = p + 1;
    while (*q == '*') {
      ++ q;
    }
    if (q != p + 1) { // has *
      for (const char* t = s; true; ++t) {
	if (isMatch(t, q)) {
	  return true;
	}
	if (*t == 0 || *t != *p && *p != '.') {
	  break;
	}
      }
    } else {
      // *s may be 0
      return (*s == *p || *s != 0 && *p == '.') && isMatch(s + 1, p + 1);
    }
    return false;
  }
};
