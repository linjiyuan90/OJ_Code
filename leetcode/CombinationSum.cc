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
    if (left >= candidates[i]) {
      cur.push_back(candidates[i]);
      combination(candidates, i, cur, left - candidates[i], ways);
      cur.pop_back();
    }
    combination(candidates, i + 1, cur, left, ways);
  }
    
public:
  vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ways;
    vector<int> cur;
    combination(candidates, 0, cur, target, ways);
    return ways;
  }
};
