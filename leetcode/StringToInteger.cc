#include "iostream"
#include "string"
#include "cctype"

class Solution {
public:
  // note:
  // if no valid conversion could be performed, return 0, like " - 321"
  // white space, +/-
  // if out of range, return INT_MAX (2147483647) or INT_MIN (-2147483648) 
  
  int atoi(const char *str) {
    int sign = 1;
    const char *p = str;
    // use std::string::find_first_not_of
    while (*p && isspace(*p)) { // trim heading spaces
      ++p;
    }
    if (*p == '-' || *p == '+') {
      sign = *p == '-' ? -1 : 1;
      ++p;
    }
    int ans = 0;
    while (*p && isdigit(*p)) {
      int d = *p++ - '0';
      // overflow
      if (INT_MAX / 10 < ans || INT_MAX / 10 == ans && d > 7) {
	return sign == 1 ? INT_MAX : INT_MIN;
      }
      // some more elegant judge
      // if (sign == 1 && (INT_MAX - d) / 10 < ans) INT_MAX
      // if (sign == -1 && (INT_MIN + d) / 10 > -ans) INT_MIN
      ans = 10 * ans + d;
    }
    return sign * ans;
  }
};

int main() {
  Solution sol;
  std::cout << sol.atoi("-2147483649) ") << std::endl;
  std::cout << sol.atoi("+21474836460) ") << std::endl;
  std::cout << sol.atoi("+2147483646) ") << std::endl;
  return 0;
}
