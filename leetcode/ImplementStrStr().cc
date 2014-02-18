class Solution {
public:
  char *strStr(char *haystack, char *needle) {
    // Note NULL situation
    if (haystack == NULL || needle == NULL) {
      return NULL;
    }
    if (*needle == 0) {
      return haystack;
    }
    int n = strlen(haystack), m = strlen(needle);
    auto next = getNext(n, needle);
    for (int i = 0, j = 0; i < n;) {
      if (haystack[i] == needle[j]) {
	++i;
	++j;
      } else {
	if (j == 0) {
	  ++i;
	} else {
	  j = next[j-1] + 1;
	}
      }
      if (j == m) {
	return haystack + i - m;
      }
    }
    return NULL;
  }
  
private:
  std::vector<int> getNext(int n, char *str) {
    std::vector<int> next(n);
    // keep: str[i] == str[next[i]]
    for (int i = 0; i < n; ++i) {
      if (i == 0) {
	next[i] = -1;
	continue;
      }
      int j = next[i-1] + 1;
      while (j >= 0 && str[i] != str[j]) {
	j = j == 0 ? -1 : next[j-1]+1;
      }
      next[i] = j;
    }
    return std::move(next);
  }
};
