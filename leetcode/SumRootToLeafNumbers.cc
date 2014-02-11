class Solution {
public:
  int sumNumbers(TreeNode *root) {
    return root == NULL ? 0 : dfs(root, 0);
  }
  int dfs(TreeNode *root, int pre) {
    pre = 10 * pre + root->val;
    if (root->left == NULL && root->right == NULL) {
      return pre;
    }
    int ans = 0;
    if (root->left != NULL) {
      ans += dfs(root->left, pre);
    }
    if (root->right != NULL) {
      ans += dfs(root->right, pre);
    }
    return ans;
  }
};
