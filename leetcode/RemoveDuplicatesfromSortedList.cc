class Solution {
public:
  ListNode *deleteDuplicates(ListNode *head) {
    if (head == NULL) {
      return head;
    }
    ListNode *p, *q;
    for (q = p = head; p; p = p->next) {
      if (p->val != q->val) {
	q->next = p;
	q = p;
      }
    }
    q->next = NULL;
    return head;
  }
};
