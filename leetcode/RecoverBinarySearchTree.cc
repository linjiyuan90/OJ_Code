class Solution {
public:
  void recoverTree(TreeNode *root) {
    std::vector<TreeNode *> err;
    TreeNode *prev = NULL;
    dfs(root, prev, err);
    // just swap head and tail nodes will work
    if (err.size() >= 2) {
      std::swap(err.front()->val, err.back()->val);
    }
  }

private:
  // Inorder traversal
  // record the strange nodes
  void dfs(TreeNode *root, TreeNode *&prev, std::vector<TreeNode *> &err) {
    if (root == NULL) {
      return;
    }
    dfs(root->left, prev, err);
    if (prev != NULL && prev->val > root->val) {
      if (err.empty() || prev != err.back()) {
	err.push_back(prev);
      }
      err.push_back(root);
    }
    prev = root;
    dfs(root->right, prev, err);
  }
};
