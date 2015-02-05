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
  int sumNumbers(TreeNode *root, int pre = 0) {
    if (root == NULL) {
      return 0;
    }
    // leaf
    if (root->left == NULL && root->right == NULL) {
      return pre * 10 + root->val;
    }
    int sum = 0;
    if (root->left != NULL) {
      sum += sumNumbers(root->left, pre*10 + root->val);
    }
    if (root->right != NULL) {
      sum += sumNumbers(root->right, pre*10 + root->val);
    }
    return sum;
  }
};
