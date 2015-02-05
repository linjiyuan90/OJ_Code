class Solution {
public:
  bool wordBreak(string s, unordered_set<string> &dict) {
    int n = s.length();
    std::vector<bool> is_feasible(n);
    for (int i = 0; i < n; ++i) {
      for (int j = i; j >= 0; --j) {
	if ((j == 0 || is_feasible[j-1])
	    && dict.count(s.substr(j, i - j + 1))) {
	  is_feasible[i] = true;
	  break;
	}
      }
    }
    return is_feasible[n-1];
  }
};
