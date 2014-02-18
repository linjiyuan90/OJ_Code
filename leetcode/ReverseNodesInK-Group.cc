class Solution {
public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    if (head == NULL || k == 1) {
      return head;
    }
    ListNode *dummy = new ListNode(0);
    ListNode *prev = dummy;
    prev->next = head;
    int c;
    for (c = 1; head != NULL && head->next != NULL; ++c) {
      if (c == k) {
	prev = head;
	head = head->next;
	c = 0;
	continue;
      }
      reverse(prev, head);
    }
    // reverse the last group back
    if (c < k) {
      for (head = prev->next; head->next != NULL; ) {
	reverse(prev, head);
      }
    }
    head = dummy->next;
    delete dummy;
    return head;
  }

private:
  void reverse(ListNode *&prev, ListNode *&head) {
    ListNode *node = head->next;
    head->next = node->next;
    node->next = prev->next;
    prev->next = node;
  }
};
