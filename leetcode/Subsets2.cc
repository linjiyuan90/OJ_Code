class Solution {
public:
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &S) {
    auto packs = pack(S);
    std::vector<std::vector<int>> ans;
    std::vector<int> subset;
    dfs(packs.begin(), packs.end(), subset, ans);
    return ans;
  }

private:

  typedef std::vector<std::pair<int, int>>::iterator Iter;
  
  void dfs(Iter beg,
	   Iter end,
	   std::vector<int> &subset,
	   std::vector<std::vector<int>> &ans) {
    if (beg == end) {
      ans.push_back(subset);
      return;
    }
    dfs(beg + 1, end, subset, ans);
    for (int n = 1; n <= beg->second; ++n) {
      subset.push_back(beg->first);
      dfs(beg + 1, end, subset, ans);
    }
    for (int n = 1; n <= beg->second; ++n) {
      subset.pop_back();
    }
  }
  
  std::vector<std::pair<int, int>> pack(std::vector<int> &S) {
    sort(S.begin(), S.end());
    std::vector<std::pair<int, int>> packs;
    for (auto e : S) {
      if (packs.empty() || packs.back().first != e) {
	packs.push_back(std::make_pair(e, 1));
      } else {
	++ packs.back().second;
      }
    }
    return packs;
  }
};
