class Solution {
public:
  std::vector<std::vector<int>> pathSum(TreeNode *root, int sum) {
    std::vector<std::vector<int>> ans;
    if (root == NULL) {
      return ans;
    }
    std::vector<int> path;
    pathSum(root, sum, path, ans);
    return ans;
  }
private:
  void pathSum(TreeNode *root,
	       int sum,
	       std::vector<int> &path,
	       std::vector<std::vector<int>> &ans) {
    path.push_back(root->val);
    sum -= root->val;
    // leaf
    if (root->left == NULL && root->right == NULL && sum == 0) {
      ans.push_back(path);
    }
    if (root->left != NULL) {
      pathSum(root->left, sum, path, ans);
    }
    if (root->right != NULL) {
      pathSum(root->right, sum, path, ans);
    }
    path.pop_back();
  }
};
