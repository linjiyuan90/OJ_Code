class Solution {
  void dfs(std::vector<int> &S, 
	   int i,
	   std::vector<int> &now,
	   std::vector<std::vector<int>> &ans) {
    if (i == S.size()) {
      ans.push_back(now);
      return;
    }
    int x = S[i];
    int ii = std::find_if_not(S.begin() + i, S.end(), std::bind1st(std::equal_to<int>(), x)) - S.begin();
    dfs(S, ii, now, ans);
    for (int j = i; j < ii; ++j) {
      now.push_back(x);
      dfs(S, ii, now, ans);
    }
    for (int j = i; j < ii; ++j) {
      now.pop_back();
    }
  }
public:
  vector<vector<int>> subsetsWithDup(vector<int> &S) {
    std::sort(S.begin(), S.end());
    std::vector<std::vector<int>> ans;
    std::vector<int> now;
    dfs(S, 0, now, ans);
    return ans;
  }
};
