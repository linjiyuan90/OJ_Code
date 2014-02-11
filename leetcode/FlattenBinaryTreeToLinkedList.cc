class Solution {
public:
  void flatten(TreeNode *root) {
    subFlatten(root);
  }

private:
  // return the last node in subtree
  TreeNode *subFlatten(TreeNode *root) {
    if (root == NULL) {
      return NULL;
    }
    // leaf
    if (root->left == NULL && root->right == NULL) {
      return root;
    }
    TreeNode *left = subFlatten(root->left);
    TreeNode *right = subFlatten(root->right);
    if (left != NULL) {
      left->right = root->right;
      root->right = root->left;
      root->left = NULL;
    }
    return right == NULL ? left : right;
  }
};
