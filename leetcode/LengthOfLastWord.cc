class Solution {
public:
  int lengthOfLastWord(const char *s) {
    int last = 0, c = 0;
    for (; *s; ++s) {
      if (isspace(*s)) {
	if (c != 0) {
	  last = c;
	}
	c = 0;
      } else {
	++ c;
      }
    }
    if (c != 0) {
      last = c;
    }
    return last;
  }
};
