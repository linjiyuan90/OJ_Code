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
  ListNode *rotateRight(ListNode *head, int k) {
    if (head == NULL) {
      return head;
    }
    int len = 0;
    for (ListNode* p = head; p != NULL; p = p->next) {
      ++ len;
    }
    k %= len;
    if (k > 0) {
      // advance len - k
      ListNode* p = head;
      for (int i = len-k-1; i--;) {
        p = p->next;
      }
      // p is the new tail
      ListNode* q = p->next;
      // advance k
      for (int i = k-1; i--; ) {
        q = q->next;
      }
      q->next = head;
      head = p->next;
      p->next = NULL;
    }
    return head;
  }
};
