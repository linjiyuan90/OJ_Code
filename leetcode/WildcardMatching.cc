class Solution {
public:
  // O(nm) dp will be TLE
  // No need to calculate fully.
    
  // https://github.com/Dionysus1227/edocteel/blob/master/Wildcard%20Matching.cc
  bool isMatch(const char *s, const char *p) {
    if (s == NULL && p == NULL) {
      return true;
    }
    if (s == NULL || p == NULL) {
      return false;
    }
    int n = ::strlen(s), m = ::strlen(p);
    int pre = 0, star = -1;
    int i = 0, j = 0;
    while (i < n) {
      if (j < m && p[j] == '*') {
	pre = i;
	star = j++;
      } else if (j < m && (p[j] == '?' || s[i] == p[j])) {
	++i;
	++j;
      } else {  // backtrack
	if (star == -1) {
	  return false;
	}
	i = ++pre;  // * match s[pre]
	j = star + 1;
      }
    }
    while (j < m && p[j] == '*') {
      ++ j;
    }
    return j == m;
  }
};

// use pre when doing a strstr~

// what about recursive solution?


