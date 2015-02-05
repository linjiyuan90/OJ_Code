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
  vector<TreeNode*> generateTrees(int n, int start = 1) {
    if (n == 0) {
      return {NULL};
    }
    vector<TreeNode*> vt;
    for (int i = 1; i <= n; ++i) {
      for (TreeNode* left : generateTrees(i-1, start)) {
        for (TreeNode* right : generateTrees(n-i, start + i)) {
          TreeNode* root = new TreeNode(start + i - 1);
          root->left = left;
          root->right = right;
          vt.push_back(root);
        }
      }
    }
    return vt;
  }
};
