class Solution {
public:
  ListNode *swapPairs(ListNode *head) {
    ListNode *dummy = new ListNode(0);
    dummy->next = head; // needed
    for (ListNode *prev = dummy; head != NULL && head->next != NULL; ) {
      ListNode *next = head->next->next;
      prev->next = head->next;
      prev->next->next = head;
      head->next = next;
      prev = head;
      head = next;
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
};
