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
  vector<int> preorderTraversal(TreeNode *root) {
    std::vector<int> ans;
    while(root != NULL) {
      if (root->left == NULL) {
	ans.push_back(root->val);
	root = root->right;
      } else {
	TreeNode* q = root->left;
	while (q->right != NULL && q->right != root) {
	  q = q->right;
	}
	// first visit
	if (q->right == NULL) {
	  ans.push_back(root->val);
	  q->right = root;
	  root = root->left;
	} else {
	  q->right = NULL;
	  root = root->right;
	}
      }
    }
    return ans;
  }
};
