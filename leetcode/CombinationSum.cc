#include "iostream"
#include "vector"
#include "algorithm"

class Solution {
public:
  // how large is target?
  // Since combinations are required to output, brute-force is as fast as knapsack.
  std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates,
						int target) {
    std::sort(candidates.begin(), candidates.end());
    candidates.erase(std::unique(candidates.begin(), candidates.end()), candidates.end());
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
    // don't choose
    dfs(ix + 1, candidates, target, ans, cur);
    if (target >= candidates[ix]) {
      // choose
      cur.push_back(candidates[ix]);
      dfs(ix, candidates, target - candidates[ix], ans, cur);
      cur.pop_back();
    }
  }
};

int main() {
  Solution sol;
  auto vt = std::vector<int> {1, 1};
  for (auto e : sol.combinationSum(vt, 1)) {
    for (auto x : e) {
      std::cout << x << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
