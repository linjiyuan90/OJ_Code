class Solution {
    
  typedef std::vector<int> int_vector;
  typedef std::vector<int_vector> int_vector2;
  typedef int_vector::iterator Iter;

  void dfs(Iter beg, Iter end,
	   int_vector2& subset,
	   int_vector& cur) {
    if (beg == end) {
      subset.push_back(cur);
      return;
    }
    dfs(beg+1, end, subset, cur);
    cur.push_back(*beg);
    dfs(beg+1, end, subset, cur);
    cur.pop_back();
  }
public:
  int_vector2 subsets(int_vector& S) {
    std::sort(S.begin(), S.end());
    int_vector2 subset;
    int_vector cur;
    dfs(S.begin(), S.end(), subset, cur);
    return subset;
  }
};
