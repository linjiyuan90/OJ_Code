class Solution {
public:
  std::vector<std::vector<int>> subsets(std::vector<int> &S) {
    std::sort(S.begin(), S.end());
    std::vector<std::vector<int>> ans;
    std::vector<int> cur;
    dfs(S.begin(), S.end(), ans, cur);
    return ans;
  }
private:
  typedef std::vector<int>::iterator Iter;

  void dfs(Iter beg, Iter end, 
	   std::vector<std::vector<int>> &ans, std::vector<int> &cur) {
    if (beg == end) {
      ans.push_back(cur);
      return;
    }
    dfs(beg + 1, end, ans, cur);
    cur.push_back(*beg);
    dfs(beg + 1, end, ans, cur);
    cur.pop_back();
  }
};
