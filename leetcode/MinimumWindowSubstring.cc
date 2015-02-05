class Solution {
public:
  string minWindow(string S, string T) {
    std::map<char, int> require;
    for (char &c : T) {
      require[c] += 1;
    }
    int need = require.size();
    std::map<char, int> have;
    std::string ans;
    for (int i = 0, j = 0, n = S.size(); i < n || j < n;) {
      if (need > 0 && j < n) {
	if (++have[S[j]] == require[S[j]]) {
	  -- need;
	}
	++j;
      } else if (need == 0 || j == n) { // when j == n, ++i
	if (have[S[i]]-- == require[S[i]]) {
	  ++ need;
	}
	++i;
      }
      if (need == 0 && (ans.empty() || ans.size() > j - i)) {
	ans = S.substr(i, j - i);
      }
    }
    return ans;
  }
};
