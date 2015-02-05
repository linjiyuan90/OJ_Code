/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  ListNode* swapPairs(ListNode* head) {
    ListNode* dummy = new ListNode(0);
    ListNode* cur = dummy;
    dummy->next = head;  // need this, since head may only have one element
    for (; head != NULL && head->next != NULL;) {
      ListNode* next = head->next->next;
      cur->next = head->next;
      cur = cur->next;
      cur->next = head;
      cur = cur->next;
      cur->next = next;
      head = next;
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
};
