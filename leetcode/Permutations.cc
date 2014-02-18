class Solution {
public:
  std::vector<std::vector<int>> permute(std::vector<int> &num) {
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
    for (int i = now; i >= 0; --i) {
      std::swap(num[i], num[now]);
      dfs(num, now + 1, ans);
      std::swap(num[i], num[now]);
    }
    // another way like permutations2
    // for (int i = now; i < num.size(); ++i)
    // this maybe more easier to understand:
    // choose one number from candidates
  }
};


// construct n-permutation from (n-1)-permutation
// enumerate the insertion positions
// But seems space expensive.
class Solution {
public:
  std::vector<std::vector<int>> permute(std::vector<int> &num) {
    return dfs(num, num.size() - 1);
  }
private:
  std::vector<std::vector<int>> dfs(std::vector<int> &num, int now) {
    std::vector<std::vector<int>> ans;
    if (now == 0) {
      ans.push_back(std::vector<int>{num[0]});
    } else {
      for (auto &e : dfs(num, now - 1)) {
	e.push_back(num[now]);
	ans.push_back(e);
	for (int i = now - 1; i >= 0; --i) {
	  std::swap(e[i], e[i+1]);
	  ans.push_back(e);
	}
      }
    }
    return ans;
  }
};
