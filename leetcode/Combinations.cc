class Solution {
public:
  std::vector<std::vector<int>> combine(int n, int k) {
    std::vector<std::vector<int>> ans;
    std::vector<int> cur;
    dfs(1, n, k, ans, cur);
    return ans;
  }

private:
  void dfs(int i, int n, int k, 
	   std::vector<std::vector<int>> &ans, std::vector<int> &cur) {
    if (cur.size() == k) {
      ans.push_back(cur);
      return;
    }
    if (i > n) {
      return;
    }
    dfs(i+1, n, k, ans, cur);
    cur.push_back(i);
    dfs(i+1, n, k, ans, cur);
    cur.pop_back();
  }
};
