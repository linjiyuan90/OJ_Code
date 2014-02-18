class Solution {
public:
  std::string countAndSay(int n) {
    std::string ans = "1";
    for (int i = 1; i < n; ++i) {
      ans = say(ans);
    }
    return ans;
  }

private:
  std::string say(std::string x) {
    if (x.empty()) {
      return "";
    }
    size_t c = x.find_first_not_of(x[0]);
    if (c == std::string::npos) {
      c = x.length();
    }
    std::stringstream sin;
    sin << c << x[0];
    return sin.str() + say(x.substr(c));
  }
};
