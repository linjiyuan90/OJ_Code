class Solution {
public:
  int maxPathSum(TreeNode *root) {
    if (root == NULL) {
      return 0;
    }
    int ans = INT_MIN;  // must choose at least one node, so ans can't be 0
    dfs(root, ans);
    return ans;
  }

  int dfs(TreeNode *root, int &ans) {
    int left = 0, right = 0;
    if (root->left != NULL) {
      left = std::max(left, dfs(root->left, ans));
    }
    if (root->right != NULL) {
      right = std::max(right, dfs(root->right, ans));
    }
    ans = std::max(ans, root->val + left + right);
    return root->val + std::max(left, right);
  }
};
