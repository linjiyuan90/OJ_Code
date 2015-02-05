class Solution {
  void traceback(
		 int now,
		 const std::string& s,
		 const std::vector<std::list<int>>& pre,
		 std::vector<std::vector<std::string>>& ans,
		 std::vector<std::string>& path) {
    if (now == -1) {
      ans.push_back(path);
      std::reverse(ans.back().begin(), ans.back().end());
      return;
    }
    for (auto& p : pre[now]) {
      path.push_back(s.substr(p, now-p+1));
      traceback(p-1, s, pre, ans, path);
      path.pop_back();
    }
  }
    
public:
  vector<vector<string>> partition(string s) {
    using std::vector;
    using std::list; 
    using std::string;
        
    // enumerate the center of palindrome
    int n = s.length();
    vector<list<int>> pre(n);
    for (int i = 0; i < n; ++i) {
      // i as center
      for (int j = 0; i-j >= 0 && i+j < n && s[i-j] == s[i+j]; ++j) {
	pre[i+j].push_back(i-j);
      }
      // middle of (i, i+1) as center
      for (int j = 0; i-j >= 0 && i+1+j < n && s[i-j] == s[i+1+j]; ++j) {
	pre[i+1+j].push_back(i-j);
      }
    }
    vector<vector<string>> ans;
    vector<string> path;
    // dfs to trace back all the combination
    traceback(s.length()-1, s, pre, ans, path);
    return ans;
  }
};
