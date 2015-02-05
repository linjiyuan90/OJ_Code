class Solution {
public:
  bool hasPathSum(TreeNode *root, int sum) {
    if (root == NULL) {
      return false;
    }
    // leaf
    if (root->left == NULL && root->right == NULL) {
      return root->val == sum;
    }
    if (root->left != NULL && hasPathSum(root->left, sum - root->val)) {
      return true;
    }
    if (root->right != NULL && hasPathSum(root->right, sum - root->val)) {
      return true;
    }
    return false;
  }
};
