class Solution {
public:
  bool isPalindrome(std::string s) {
    std::string t;
    for (auto c : s) {
      if (::isalnum(c)) {
	t += ::tolower(c);
      }
    }
    std::string r = t;
    std::reverse(r.begin(), r.end());
    return t == r;
  }
};
// TODO
// Without constructing new string
