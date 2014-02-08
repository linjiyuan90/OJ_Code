
class Solution {
public:
  bool wordBreak(std::string s, std::unordered_set<std::string> &dict) {
    std::vector<bool> dp(s.length() + 1, false);
    dp[0] = true;
    for(size_t ix = 0; ix < s.length(); ++ix) {
      for (auto w : dict) {
	if (w.length() <= ix + 1) {
	  size_t beg  = ix + 1 - w.length();
	  if (dp[beg] && s.substr(beg, w.length()) == w) {
	    dp[ix + 1] = true;
	    break;
	  }
	}
      }
    }
    return dp[s.length()];
  }
};
