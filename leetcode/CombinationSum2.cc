class Solution {
public:
  std::vector<std::vector<int>> combinationSum2(std::vector<int> &candidates,
						int target) {
    std::sort(candidates.begin(), candidates.end());
    std::vector<std::vector<int>> ans;
    std::vector<int> cur;
    dfs(0, candidates, target, ans, cur);
    return ans;
  }

private:
  void dfs(int ix,
	   std::vector<int> &candidates,
	   int target,
	   std::vector<std::vector<int>> &ans,
	   std::vector<int> &cur) {
    if (target == 0) {
      ans.push_back(cur);
      return;
    }
    if (ix == candidates.size()) {
      return;
    }
    int next = ix + 1;
    while (next < candidates.size() && candidates[next] == candidates[ix]) {
      ++ next;
    }
    // don't choose
    dfs(next, candidates, target, ans, cur);
    // choose one, two, ...
    int c = 0;
    for (; ix < next && target >= candidates[ix]; ++ix, ++c) {
      cur.push_back(candidates[ix]);
      target -= candidates[ix];
      dfs(next, candidates, target, ans, cur);
    }
    while (c--) {
      cur.pop_back();
    }
  }
};

// [1, 1], 1 return [{1}]
