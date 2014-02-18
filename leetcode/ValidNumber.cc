class Solution {
public:
  bool isNumber(const char *s) {
    ignore_space(s);
    ignore_sign(s);
    bool first = ignore_digit(s), second = true, third = true;
    if (*s == '.') {
      ++s;
      second = ignore_digit(s);
      if (first) {  // 1.
	second = true;
      }
      if (second) {  // .1
	first = true;
      }
    }
    if (first && second && (*s == 'e' || *s == 'E')) {
      ++s;
      ignore_sign(s);
      third = ignore_digit(s);
    }
    ignore_space(s);
    return first && second && third && *s == 0;
  }

private:
  bool ignore_space(const char *&s) {
    const char *p = s;
    while (isspace(*s)) {
      ++s;
    }
    return p != s;
  }
  bool ignore_digit(const char *&s) {
    const char *p = s;
    while (isdigit(*s)) {
      ++s;
    }
    return p != s;
  }
  bool ignore_sign(const char *&s) {
    if (*s == '-' || *s == '+') {
      ++s;
    }
  }
};

// 46.e3
// -1.
// .e1
