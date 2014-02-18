class Solution {
public:
  ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode *dummy = new ListNode(0), *head = dummy;
    while (l1 != NULL || l2 != NULL) {
      if (l1 == NULL || l2 != NULL && l1->val > l2->val) {
	head->next = l2;
	l2 = l2->next;
	head = head->next;
      } else {
	head->next = l1;
	l1 = l1->next;
	head = head->next;
      }
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
};
