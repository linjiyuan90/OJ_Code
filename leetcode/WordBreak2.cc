class Solution {
public:
  std::vector<std::string> wordBreak(std::string s, 
				     std::unordered_set<std::string> &dict) {
    std::vector<std::vector<int>> dp(s.length() + 1, std::vector<int>());
    dp[0].push_back(0);
    for (size_t ix = 0; ix < s.length(); ++ix) {
      for (auto w : dict) {
	if (ix + 1 >= w.length()) {
	  size_t beg = ix + 1 - w.length();
	  if (!dp[beg].empty() && s.substr(beg, w.length()) == w) {
	    dp[ix+1].push_back(w.length());
	  }
	}
      }
    }
    std::vector<std::string> ans;
    backtrack(s.length(), s, dp, ans, "");
    return ans;
  }

private:
  void backtrack(size_t now,
		 const std::string &s,
		 const std::vector<std::vector<int>> &dp,
		 std::vector<std::string> &ans,
		 std::string tail) {
    if (now == 0) {
      ans.push_back(tail);
      return;
    }
    for (auto l : dp[now]) {
      if (now == s.length()) {
	backtrack(now - l, s, dp, ans, s.substr(now - l, l));
      } else {
	backtrack(now - l, s, dp, ans, s.substr(now - l, l) + " " + tail);
      }
    }
  }
};
