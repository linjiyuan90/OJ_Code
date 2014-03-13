class Solution {
public:
  char *strStr(char *haystack, char *needle) {
    if (haystack == NULL || needle == NULL) {
      return haystack;
    }
    if (*needle == 0) { // ""
      return haystack;
    }
    int n = strlen(haystack), m = strlen(needle);
    auto next = calc_next(needle, m);
    for (int i = 0, j = 0; i < n;) {
      if (haystack[i] == needle[j]) {
	++i;
	++j;
	if (j == m) {
	  return haystack + (i - m);
	}
      } else {
	if (j == 0) {
	  ++ i;
	} else {
	  j = next[j-1] + 1;
	}
      }
    }
    return NULL;
  }

private:
  // keep s[i] = s[next[i]]
  std::vector<int> calc_next(char *s, int n) {
    auto next = std::vector<int>(n);
    if (n > 0) {
      next[0] = -1;
      for (int i = 1, j; i < n; ++i) {
	for (j = next[i-1] + 1; j >= 0 && s[j] != s[i];) {
	  j = j == 0 ? -1 :  next[j-1] + 1;
	}
	next[i] = j;
      }
    }
    return std::move(next);
  }  
};
