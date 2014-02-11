class Solution {
public:
  bool hasPathSum(TreeNode *root, int sum) {
    if (root == NULL) {
      return false;
    }
    // Note it's root-to-leaf
    if (root->left == NULL && root->right == NULL) {
      return sum == root->val;
    }
    return hasPathSum(root->left, sum - root->val) || 
      hasPathSum(root->right, sum - root->val);
  }
};
