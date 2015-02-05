class Solution {
  // judge [+-]a.b
  bool isDecimal(const char*& p, bool checkFloat) {
    if (*p == '+' || *p == '-') {
      ++ p;
    }
    bool hasDigit = ::isdigit(*p);
    while(::isdigit(*p)) ++p;
    if (checkFloat && *p == '.') {
      ++ p;
      hasDigit |= ::isdigit(*p);
      while(::isdigit(*p)) ++p;
    }
    return hasDigit;
  }
    
public:
  bool isNumber(const char *p) {
    while(::isspace(*p)) ++p;
    // [+-]a.be[+-]c.d
    if (!isDecimal(p, true)) {
      return false;
    }
    if (*p == 'e') {
      ++ p;
      if (!isDecimal(p, false)) {
        return false;
      }
    }
    while(::isspace(*p)) ++p;
    return *p == 0;
  }
};

// note case '.', "6e6.5"
