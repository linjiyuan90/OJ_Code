class Solution {
public:
  std::vector<std::vector<int> > levelOrderBottom(TreeNode *root) {
    std::vector<std::vector<int>> ans;
    if (root == NULL) {
      return ans;
    }
    for (std::vector<TreeNode *> last{root}; !last.empty(); ) {
      ans.push_back(std::vector<int>());
      std::vector<TreeNode *> next;
      for (TreeNode *node : last) {
	ans.back().push_back(node->val);
	if (node->left != NULL) {
	  next.push_back(node->left);
	}
	if (node->right != NULL) {
	  next.push_back(node->right);
	}
      }
      last = next;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};
