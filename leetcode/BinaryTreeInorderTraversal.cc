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
  // morris inorder
  // what's the time complexity? O(n^2)?
  std::vector<int> inorderTraversal(TreeNode *root) {
    std::vector<int> orders;
    while (root != NULL) {
      if (root->left != NULL) {
	TreeNode *p = root->left;
	while (p->right != root && p->right != NULL) {
	  p = p->right;
	}
	if (p->right == root) {
	  orders.push_back(root->val);
	  p->right = NULL;
	  root = root->right;
	} else {
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
  for (auto e : sol.inorderTraversal(root)) {
    std::cout << e << " ";
  }
  return 0;
}
