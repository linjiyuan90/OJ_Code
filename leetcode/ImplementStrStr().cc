class Solution {
  std::vector<int> getNext(const std::string& str) {
    if (str.empty()) {  // note
      return std::vector<int>();
    }
    int n = str.size();
    std::vector<int> next(n);
    next[0] = -1;
    for (int i = 1; i < n; ++i) {
      for (next[i] = next[i-1] + 1; next[i] >= 0 && str[next[i]] != str[i]; ) {
	next[i] = next[i] == 0 ? -1 : next[next[i]-1] + 1;
      }
    }
    return next;
  }
    
public:
  char *strStr(char *haystack, char *needle) {
    if (haystack == NULL || needle == NULL) {
      return NULL;
    }
    auto next = getNext(needle);
    int n = ::strlen(haystack);
    int m = ::strlen(needle);
    int i, j;
    for (i = 0, j = 0; i < n && j < m; ) {
      if (haystack[i] == needle[j]) {
	++ i;
	++ j;
      } else {
	for (; j >= 0 && haystack[i] != needle[j]; ) {
	  j = j == 0 ? -1 : next[j-1] + 1;
	}
	if (j == -1) {
	  j = 0;
	  ++ i;
	}
      }
    }
    return j == m ? haystack + (i - m) : NULL;
  }
};
