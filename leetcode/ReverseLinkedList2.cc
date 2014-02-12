class Solution {
public:
  ListNode *reverseBetween(ListNode *head, int m, int n) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *cur = head;
    head = dummy;
    for (int c = 1; c < n; ++c) {
      if (c < m) {
	head = head->next;
	cur = cur->next;
      } else {
	ListNode *node = cur->next;
	// nice by changing cur->next
	cur->next = node->next;
	node->next = head->next;
	head->next = node;
      }
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
};
