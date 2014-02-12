class Solution {
public:
  int lengthOfLongestSubstring(std::string s) {
    std::unordered_map<char, int> last;
    int ans = 0; // note empty string
    for (int i = 0, j = 0; j < s.length(); ++j) {
      if (last.count(s[j])) {
	// just jump :-)
	i = std::max(i, last[s[j]] + 1);
      }
      last[s[j]] = j;
      ans = std::max(ans, j - i + 1);
    }
    return ans;
  }
};
