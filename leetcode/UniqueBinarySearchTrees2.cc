#include "iostream"
#include "algorithm"
#include "vector"
#include "numeric"

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int val): val(val) {}
};

int tot;

class Solution {
public:
  std::vector<TreeNode *> generateTrees(int n) {
    return generateTrees(1, n);
  }
  
private:
  // TODO
  // how many nodes are 'new' in fact?
  std::vector<TreeNode *> generateTrees(int left, int right) {
    if (left > right) {
      return std::vector<TreeNode *>{NULL};
    }
    std::vector<TreeNode *> ans;
    for (int r = left; r <= right; ++r) {
      for (auto l_root : generateTrees(left, r - 1)) {
	for (auto r_root : generateTrees(r + 1, right)) {
	  TreeNode *root = new TreeNode(r);
	  ++ tot;
	  root->left = l_root;
	  root->right = r_root;
	  ans.push_back(root);
	}
      }
    }
    return ans;
  }
};

int main() {
  std::vector<int> dp(10);
  dp[0] = 1;
  for (int n = 1; n < 5; ++n) {
    for (int l_size = 0; l_size < n; ++ l_size) {
      dp[n] += dp[l_size] * dp[n - 1 - l_size];
    }
    tot = 0;
    Solution sol;
    sol.generateTrees(n);
    std::cout << n << ": " << tot << std::endl;
    tot = 0;
    for (int i = 1; i <= n; ++i) {
      int s = 0;
      for (int l = 0; l < i; ++l) {
	for (int r = 0; i+r <= n; ++r) {
	  s += dp[l] * dp[r];
	}
      }
      std::cout << i << " " << s << std::endl;
      tot += s;
    }
    std::cout << tot << std::endl;
  }
  return 0;
}
