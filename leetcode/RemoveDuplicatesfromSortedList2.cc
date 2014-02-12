class Solution {
public:
  ListNode *deleteDuplicates(ListNode *head) {
    if (head == NULL) {
      return head;
    }
    ListNode *dummy = new ListNode(head->val-1);
    ListNode *pre = dummy, *cur = head;
    head = dummy;
    for (; cur != NULL; pre = cur, cur = cur->next) {
      if (pre->val == cur->val) {
	continue;
      }
      if (cur->next == NULL || cur->val != cur->next->val) {
	head->next = cur;
	head = head->next;
      }
    }
    head->next = NULL;
    head = dummy->next;
    delete dummy;
    return head;
  }
};
