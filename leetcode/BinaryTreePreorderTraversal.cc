class Solution {
public:
  // morris preorder
  std::vector<int> preorderTraversal(TreeNode *root) {
    std::vector<int> orders;
    while (root != NULL) {
      if (root->left != NULL) {
	TreeNode *p = root->left;
	while (p->right != root && p->right != NULL) {
	  p = p->right;
	}
	if (p->right == root) {
	  p->right = NULL;
	  root = root->right;
	} else {
	  orders.push_back(root->val);
	  p->right = root;
	  root = root->left;
	}
      } else {
	orders.push_back(root->val);
	root = root->right;
      }
    }
    return orders;
  }
};
