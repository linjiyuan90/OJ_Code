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
  bool isValidBST(TreeNode *root, int* pre = new int(numeric_limits<int>::min())) {
    if (root == NULL) {
      return true;
    }
    if (!isValidBST(root->left, pre) || *pre >= root->val) {
      return false;
    }
    *pre = root->val;
    return isValidBST(root->right, pre);
  }
};
