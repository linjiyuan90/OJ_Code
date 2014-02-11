class Solution {
public:
  int minDepth(TreeNode *root) {
    if (root == NULL) {
      return 0;
    }
    if (root->left == NULL && root->right == NULL) {
      return 1;
    }
    int ans = INT_MAX;
    if (root->left != NULL) {
      ans = std::min(ans, minDepth(root->left) + 1);
    }
    if (root->right != NULL) {
      ans = std::min(ans, minDepth(root->right) + 1);
    }
    return ans;
  }
};
