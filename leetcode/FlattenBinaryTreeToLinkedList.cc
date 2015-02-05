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
  TreeNode* flattenWithLast(TreeNode* root) {
    if (root == NULL) {
      return NULL;
    }
    TreeNode* last = root;
    if (last->left) {
      last = flattenWithLast(last->left);
      last->right = root->right;
      root->right = root->left;
      root->left = NULL;
    }
    if (last->right) {
      last = flattenWithLast(last->right);
    }
    return last;
  }
public:
  void flatten(TreeNode* root) {
    flattenWithLast(root);
  }
};
