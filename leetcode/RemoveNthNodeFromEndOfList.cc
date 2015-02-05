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
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* p = dummy;
    while (n > 0) {
      p = p->next;
      --n;
    }
    ListNode* q = dummy;
    while (p->next) {
      q = q->next;
      p = p->next;
    }
    p = q->next;
    q->next = p->next;
    head = dummy->next;
    delete p;
    delete dummy;
    return head;
  }
};
