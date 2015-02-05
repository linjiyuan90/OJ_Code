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
  void pathSum(TreeNode* root, int need, std::vector<int>& path, std::vector<std::vector<int>>& ans) {
    path.push_back(root->val);
    need -= root->val;
    if (root->left == NULL && root->right == NULL) {  // leaf
      if (need == 0) {
	ans.push_back(path);
      }
    } else {
      if (root->left) {
	pathSum(root->left, need, path, ans);
      }
      if (root->right) {
	pathSum(root->right, need, path, ans);
      }
    }
    path.pop_back();
  }
    
public:
  vector<vector<int> > pathSum(TreeNode *root, int sum) {
    std::vector<std::vector<int>> ans;
    if (root != NULL) {
      std::vector<int> path;
      pathSum(root, sum, path, ans);
    }
    return ans;
  }
};
