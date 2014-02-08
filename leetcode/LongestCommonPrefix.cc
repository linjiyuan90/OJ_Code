class Solution {
public:
  string longestCommonPrefix(vector<string> &strs) {
    int ans = strs.empty() ? 0 : strs[0].length();
    for (size_t ix = 1; ans > 0 && ix < strs.size(); ++ix) {
      int c = 0;
      while (strs[ix][c] == strs[ix-1][c] && c < ans) {
	c ++;
      }
      ans = min(ans, c);
    }
    return strs.empty() ? "" : strs[0].substr(0, ans);
  }
};