class Solution {
public:
  int numDecodings(std::string s) {
    // note
    if (s.empty()) {
      return 0;
    }
    std::vector<int> dp(s.length() + 1);
    dp[0] = 1;
    for (int i = 1; i <= s.length(); ++i) {
      if (s[i-1] != '0') {
	dp[i] += dp[i-1];
      }
      if (s[i-2] != '0' && i > 1 && (s[i-2] - '0') * 10 + s[i-1]-'0' <= 26) {
	dp[i] += dp[i-2];
      }
    }
    return dp[s.length()];
  }
};
