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
  bool isSymmetric(TreeNode *p, TreeNode* q) {
    if (p == NULL && q == NULL) {
      return true;
    }
    if (p == NULL || q == NULL) {
      return false;
    }
    return p->val == q->val &&
      isSymmetric(p->left, q->right) && 
      isSymmetric(p->right, q->left);
  }
public:
  bool isSymmetric(TreeNode*& root) {
    return root == NULL || isSymmetric(root->left, root->right);
  }
};
