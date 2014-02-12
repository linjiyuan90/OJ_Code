class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *dummy = new ListNode(0);
    ListNode *prev = dummy;
    for (; l1 != NULL || l2 != NULL; ) {
      if (prev->next == NULL) {
	prev->next = new ListNode(0);
      }
      if (l1 != NULL) {
	prev->next->val += l1->val;
	l1 = l1->next;
      }
      if (l2 != NULL) {
	prev->next->val += l2->val;
	l2 = l2->next;
      }
      if (prev->next->val >= 10) {
	prev->next->val -= 10;
	prev = prev->next;
	prev->next = new ListNode(1);
      } else {
	prev = prev->next;
      }
    }
    prev = dummy->next;
    delete dummy;
    return prev;
  }
};
