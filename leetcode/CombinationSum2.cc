class Solution {
    
  void combination(vector<int>& candidates, int i, vector<int>& cur, int left, vector<vector<int>>& ways) {
    if (left == 0) {
      if (!cur.empty()) {
        ways.push_back(cur);
      }
      return;
    }
    if (i == candidates.size()) {
      return;
    }
    int j = upper_bound(candidates.begin() + i, candidates.end(), candidates[i]) - candidates.begin();
    int k = 0;
    for (; left >= 0 && k <= j - i; ++k) {
      combination(candidates, j, cur, left, ways);
      cur.push_back(candidates[i]);
      left -= candidates[i];
    }
    while (k--) {
      cur.pop_back();
    }
  }
    
public:
  vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ways;
    vector<int> cur;
    combination(candidates, 0, cur, target, ways);
    return ways;
  }
};
