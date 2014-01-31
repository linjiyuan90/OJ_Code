#include "iostream"
#include "vector"
#include "stack"

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  // Is there a 'Morris-like' solution?
  std::vector<int> postorderTraversal(TreeNode *root) {
    std::vector<int> orders;
    std::stack<TreeNode *> stack;
    if (root != NULL) {
      stack.push(root);
    }
    TreeNode *prev = NULL;
    while (!stack.empty()) {
      TreeNode *u = stack.top();
      stack.pop();
      // leaf
      if (u->left == NULL && u->right == NULL) {
	orders.push_back(u->val);
      } else if (prev != NULL && (u->left == prev || u->right == prev)) {
	// second time
	orders.push_back(u->val);
      } else {
	// first time
	stack.push(u);
	if(u->right != NULL) {
	  stack.push(u->right);
	}
	if (u->left != NULL) {
	  stack.push(u->left);
	}
      }
      prev = u;
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
  for (auto e : sol.postorderTraversal(root)) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
  return 0;
}
