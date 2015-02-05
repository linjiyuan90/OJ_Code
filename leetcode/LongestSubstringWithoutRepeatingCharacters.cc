class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int ans = 0;
    std::map<char, int> char_cnt;
    for (size_t l = 0, r = 0, n = s.size(); l < n || r < n;) {
      if (r < n && char_cnt[s[r]] == 0) { // NOT !char_cnt.count(s[r])
	++ char_cnt[s[r++]];
      } else {
	-- char_cnt[s[l++]];
      }
      ans = std::max(ans, static_cast<int>(r - l));
    }
    return ans;
  }
};
