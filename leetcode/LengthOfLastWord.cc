class Solution {
public:
  int lengthOfLastWord(const char *s) {
    int n = ::strlen(s);
    const char* p = s + n;
    while (p != s && ::isspace(*(p-1))) --p;
    const char* end = p;
    while (p != s && !::isspace(*(p-1))) --p;
    const char* beg = p;
    return end - beg;
  }
};
