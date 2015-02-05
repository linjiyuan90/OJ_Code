class Solution {
  void dfs(int n,
	   int r,
	   int left,
	   int vertical,
	   int right,
	   std::vector<std::string> &prev,
	   std::vector<std::vector<std::string>>&ans) {
    if (r == n) {
      ans.push_back(prev);
      return;
    }
    int ok = ((1<<n) - 1) & ~(left | vertical | right);
    std::string row(n, '.');
    for (int i = 0; i < n; ++i) {
      if (ok & (1 << i)) {
	row[i] = 'Q';
	prev.push_back(row);
	dfs(n, r + 1, 
	    (left | (1<<i)) << 1, 
	    vertical | (1<<i), 
	    (right | (1<<i)) >> 1,
	    prev,
	    ans);
	prev.pop_back();
	row[i] = '.';
      }
    }
  }
public:
  vector<vector<string> > solveNQueens(int n) {
    std::vector<std::vector<std::string>> ans;
    std::vector<std::string> prev;
    dfs(n, 0, 0, 0, 0, prev, ans);
    return ans;
  }
};
