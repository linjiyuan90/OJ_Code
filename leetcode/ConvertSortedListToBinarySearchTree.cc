/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
  TreeNode* sortedListToBST(ListNode*& head, int n) {
    if (n == 0) {
      return NULL;
    }
    TreeNode* left = sortedListToBST(head, n/2);
    TreeNode* root = new TreeNode(head->val);
    head = head->next;
    TreeNode* right = sortedListToBST(head, n-n/2-1);
    root->left = left;
    root->right = right;
    return root;
  }
    
public:
  TreeNode* sortedListToBST(ListNode* head) {
    int n = 0;
    for (ListNode* p = head; p != NULL; p = p->next) ++n;
    return sortedListToBST(head, n);
  }
};
