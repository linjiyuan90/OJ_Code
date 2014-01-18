class Solution {
public:
  ListNode *deleteDuplicates(ListNode *head) {
    if (head == NULL) {
      return NULL;
    }
    ListNode *a = NULL, *b = NULL, *c = head;
    ListNode *q = new ListNode(0);
    head = q;
    for (; ; a = b, b = c, c = c->next) {
      if (b != NULL && (c == NULL || b->val != c->val)) {
	if (a == NULL || a->val != b->val) {
	  q = q->next = b;
	}
      }
      if (c == NULL) {
	break;
      }
    }
    q->next = NULL;
    return head->next;
  }
};
