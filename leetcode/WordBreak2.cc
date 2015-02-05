/*
  Need to do a dp first.
  Just dfs will TLE, since when searching, push & pop too much.
*/

class Solution {
  std::vector<std::vector<int>> findBreaks(
					   const std::string& s,
					   std::unordered_set<std::string>& dict) {
    int n = s.length();
    std::vector<std::vector<int>> breaks(n);
    for (int i = 0; i < n; ++i) {
      for (int j = i; j >= 0; --j) {
	if ((j == 0 || !breaks[j-1].empty())
	    && dict.count(s.substr(j, i - j + 1))) {
	  breaks[i].push_back(j);
	}
      }
    }
    return breaks;
  }
    
  void gather(const std::string&s,
	      int now,
	      std::vector<int>& path,
	      std::vector<std::vector<int>>& breaks,
	      std::vector<std::string>& ans) {
    if (now == -1) {
      std::string words;
      int ix = 0;
      for (auto it = path.rbegin()+1; it != path.rend(); ++it) {
	if (ix > 0) {
	  words += " ";
	}
	words += s.substr(ix, *it - ix);
	ix = *it;
      }
      ans.push_back(words);
      return;
    }
    for (auto& b : breaks[now]) {
      path.push_back(b);
      gather(s, b-1, path, breaks, ans);
      path.pop_back();
    }
  }
    
public:
  vector<string> wordBreak(string s, unordered_set<string> &dict) {
    auto breaks = findBreaks(s, dict);
    std::vector<std::string> ans;
    std::vector<int> path;
    path.push_back(s.length());
    gather(s, s.length() - 1, path, breaks, ans);
    return ans;
  }
};
