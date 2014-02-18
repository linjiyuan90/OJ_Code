class Solution {
public:
  std::vector<std::vector<int>> permuteUnique(std::vector<int> &num) {
    std::vector<std::vector<int>> ans;
    dfs(num, 0, ans);
    return ans;
  }
private:
  void dfs(std::vector<int> &num, int now, std::vector<std::vector<int>> &ans) {
    if (now == num.size()) {
      ans.push_back(num);
      return;
    }
    std::set<int> have;
    for (int i = now; i < num.size(); ++i) {
      if (have.count(num[i]) == 0) {
	std::swap(num[i], num[now]);
	dfs(num, now + 1, ans);
	std::swap(num[i], num[now]);
	have.insert(num[i]);
      }
    }
  }
};
