#include "iostream"
#include "vector"


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

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

int main() {
  TreeNode *root = new TreeNode(1);
  TreeNode *two = new TreeNode(2);
  two->left = new TreeNode(3);
  root->right = two;
  Solution sol;
  for (auto e : sol.preorderTraversal(root)) {
    std::cout << e << " ";
  }
  return 0;
}
