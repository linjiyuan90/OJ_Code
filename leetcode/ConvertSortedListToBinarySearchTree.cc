// naive solution
class Solution {
public:
  TreeNode *sortedListToBST(ListNode *head) {
    if (head == NULL) {
      return NULL;
    }
    int n = 0;
    for (ListNode *q = head; q != NULL; q = q->next) {
      ++n;
    }
    if (n == 1) {
      return new TreeNode(head->val);
    }
    ListNode *q = head;
    for (int c = 0; c < n/2 - 1; ++c) {
      q = q->next;
    }
    ListNode *list_root = q->next;
    q->next = NULL;
    TreeNode *root = new TreeNode(list_root->val);
    root->left = sortedListToBST(head);
    root->right = sortedListToBST(list_root->next);
    // recover
    q->next = list_root;
    return root;
  }
};


// O(n)!!
class Solution {
public:
  TreeNode *sortedListToBST(ListNode *head) {
    int n = 0;
    for (ListNode *q = head; q != NULL; q = q->next) {
      ++ n;
    }
    return build_BST(head, n);
  }
  
private:
  // move head!!
  TreeNode *build_BST(ListNode *&head, int n) {
    if (n == 0) {
      return NULL;
    }
    TreeNode *cur = new TreeNode(0);
    cur->left = build_BST(head, n/2);
    cur->val = head->val;
    head = head->next;
    cur->right = build_BST(head, n - 1 - n/2);
    return cur;
  }
};
