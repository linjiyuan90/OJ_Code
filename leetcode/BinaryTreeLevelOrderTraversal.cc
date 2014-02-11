class Solution {
public:
  
  std::vector<std::vector<int>> levelOrder(TreeNode *root) {
    std::vector<std::vector<int>> ans;
    dfs(root, 0, ans);
    return ans;
  }
  
private:
  // recursive is more beautiful
  void dfs(TreeNode *root, int dep, std::vector<std::vector<int>> &ans) {
    if (root == NULL) {
      return;
    }
    if (dep >= ans.size()) {
      ans.push_back(std::vector<int>());
    }
    ans[dep].push_back(root->val);
    dfs(root->left, dep + 1, ans);
    dfs(root->right, dep + 1, ans);
  }
};
