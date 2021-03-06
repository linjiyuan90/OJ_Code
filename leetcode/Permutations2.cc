class Solution {
  typedef std::vector<int> int_vector;
  typedef std::vector<int_vector> int_vector2;
    
  void dfs(int_vector& num, int now, int_vector2& ans) {
    if (now == num.size()) {
      ans.push_back(num);
      return;
    }
    std::set<int> visit;
    for (int i = now; i < num.size(); ++i) {
      if (visit.count(num[i])) {
	continue;
      }
      visit.insert(num[i]);
      std::swap(num[now], num[i]);
      dfs(num, now+1, ans);
      std::swap(num[now], num[i]);
    }
  }
    
public:
  int_vector2 permuteUnique(int_vector& num) {
    int_vector2 ans;
    dfs(num, 0, ans);
    return ans;
  }
};
