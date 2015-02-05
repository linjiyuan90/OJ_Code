/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
  TreeLinkNode* traverse(TreeLinkNode* head) {
    TreeLinkNode* next = head->left;
    if (next != NULL) {
      for (; head != NULL; head = head->next) {
	head->left->next = head->right;
	if (head->next) {
	  head->right->next = head->next->left;
	}
      }
    }
    return next;
  }
public:
  void connect(TreeLinkNode* root) {
    // traverse and link next level's nodes
    while(root) {
      root = traverse(root);
    }
  }
};
