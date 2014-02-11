class Solution {
public:
  bool isBalanced(TreeNode *root) {
    return height_balance(root).second;
  }
  
private:
  // (height, balanceOrNot)
  std::pair<int, bool> height_balance(TreeNode *root) {
    if (root == NULL) {
      return std::make_pair(0, true);
    }
    auto left = height_balance(root->left);
    auto right = height_balance(root->right);
    if (!left.second || !right.second) {
      return std::make_pair(0, false);
    }
    return
      std::make_pair(1 + std::max(left.first, right.first), 
		     abs(left.first - right.first) <= 1);
  }
};
