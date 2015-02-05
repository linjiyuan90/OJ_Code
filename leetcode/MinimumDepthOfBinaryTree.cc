/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  int minDepth(TreeNode *root) {
    if (root == NULL) {
      return 0;
    }
    // leaf
    if (root->left == NULL && root->right == NULL) {
      return 1;
    }
    int ans = INT_MAX;
    if (root->left != NULL) {
      ans = std::min(ans, 1 + minDepth(root->left));
    }
    if (root->right != NULL) {
      ans = std::min(ans, 1 + minDepth(root->right));
    }
    return ans;
  }
};
