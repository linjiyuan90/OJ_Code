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
    TreeLinkNode* next = NULL;
    TreeLinkNode* pre = NULL;
    for (; head; head = head->next) {
      if (head->left) {
	if (pre != NULL) {
	  pre->next = head->left;
	}
	pre = head->left;
	if (next == NULL) {
	  next = head->left;
	}
      }
      if (head->right) {
	if (pre != NULL) {
	  pre->next = head->right;
	}
	pre = head->right;
	if (next == NULL) {
	  next = head->right;
	}
      }
    }
    return next;
  }
public:
  void connect(TreeLinkNode* root) {
    while(root) {
      root = traverse(root);
    }
  }
};
