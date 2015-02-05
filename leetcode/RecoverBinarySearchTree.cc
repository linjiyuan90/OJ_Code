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
    
  void recoverTreeImpl(TreeNode* root, TreeNode*& pre, vector<TreeNode*>& err) {
    if (root == NULL) {
      return;
    }
    recoverTreeImpl(root->left, pre, err);
    // whenever there is a descend pair, record them.
    if (pre != NULL && pre->val > root->val) {
      if (err.empty() || pre != err.back()) {
        err.push_back(pre);
      }
      err.push_back(root);
    }
    pre = root;
    recoverTreeImpl(root->right, pre, err);
  }
    
public:
  void recoverTree(TreeNode *root) {
    vector<TreeNode*> err;
    TreeNode* pre = NULL;
    recoverTreeImpl(root, pre, err);
    if (err.size() >= 2) {
      swap(err.front()->val, err.back()->val);
    }
  }
};


//   1 2 7 4 5 6 3
