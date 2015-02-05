class Solution {
    
  typedef std::vector<int> int_vector;
  typedef std::vector<int_vector> int_vector2;
    
  void dfs(int i, int n, int k, int_vector2& ans, int_vector& cur) {
    if (cur.size() == k) {
      ans.push_back(cur);
      return;
    }
    if (i == n+1) {
      return;
    }
    dfs(i+1, n, k, ans, cur);
    cur.push_back(i);
    dfs(i+1, n, k, ans, cur);
    cur.pop_back();
  }
    
public:
  int_vector2 combine(int n, int k) {
    int_vector2 ans;
    int_vector cur;
    dfs(1, n, k, ans, cur);
    return ans;
  }
};
