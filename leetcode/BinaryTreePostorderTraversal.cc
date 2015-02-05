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
public:
  // Almost same as preorder traversal
  // Just swap the left and right
  // Finally, reverse the res
  vector<int> postorderTraversal(TreeNode *root) {
    std::vector<int> res;
    while(root != NULL) {
      if (root->right) {
	TreeNode* p = root->right;
	while(p->left != NULL && p->left != root) {
	  p = p->left;
	}
	if (p->left == NULL) {  // first time
	  res.push_back(root->val);
	  p->left = root;
	  root = root->right;
	} else {
	  p->left = NULL;
	  root = root->left;
	}
      } else {
	res.push_back(root->val);
	root = root->left;
      }
    }
    std::reverse(res.begin(), res.end());
    return res;
  }
};
