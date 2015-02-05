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
    
  const int MIN = std::numeric_limits<int>::min();
    
  int dfs(TreeNode* root, int& ans) {
    int left = 0, right = 0;
    if (root->left != NULL) {
      left = std::max(left, dfs(root->left, ans));
    }
    if (root->right != NULL) {
      right = std::max(right, dfs(root->right, ans));
    }
    ans = std::max(ans, left + right + root->val);
    return std::max(left, right) + root->val;
  }
    
public:
  int maxPathSum(TreeNode *root) {
    if (root == NULL) {
      return 0;
    }
    int ans = MIN;
    dfs(root, ans);
    return ans;
  }
};
