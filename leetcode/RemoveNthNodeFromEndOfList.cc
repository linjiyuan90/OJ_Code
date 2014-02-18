class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *prev = dummy;
    for (int c = 1; c <= n; ++c) {
      head = head->next;
    }
    while (head != NULL) {
      prev = prev->next;
      head = head->next;
    }
    head = prev->next;
    prev->next = head->next;
    delete head;
    head = dummy->next;
    delete dummy;
    return head;
  }
};
