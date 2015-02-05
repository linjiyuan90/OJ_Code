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
  std::pair<bool, int> isBalancedWithHeight(TreeNode *root) {
    if (root == NULL) {
      return {true, 0};
    }
    auto left = isBalancedWithHeight(root->left);
    auto right = isBalancedWithHeight(root->right);
    if (left.first && right.first && ::abs(left.second - right.second) <= 1) {
      return {true, std::max(left.second, right.second) + 1};            
    }
    return {false, -1};
  }
    
public:
  bool isBalanced(TreeNode *root) {
    return isBalancedWithHeight(root).first;
  }
};
