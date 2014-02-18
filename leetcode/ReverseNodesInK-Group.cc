class Solution {
public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *dummy = new ListNode(0);
    ListNode *prev = dummy;
    for (int c = 0; head != NULL; ++c) {
      if (c == k) {
	c = 0;
      }
      ListNode *node = head->next;
      head->next = head->next->next;
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
};
