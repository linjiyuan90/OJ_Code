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
  ListNode *detectCycle(ListNode *head) {
    // check whether there is a cycle
    ListNode* p = head;
    ListNode* q = head;
    for (; p != NULL && q != NULL;) {
      p = p->next;
      q = q->next;
      if (q != NULL) {
	q = q->next;
      }
      if (p == q) {
	break;
      }
    }
    if (p == NULL || q == NULL) {
      return NULL;
    }
    // loop again to find the length of the cycle
    int n = 0;
    for (; n == 0 || p != q; ++n) {
      p = p->next;
      q = q->next->next;
    }
    q = p = head;
    // advance q n steps
    for (int i = 0; i < n; ++i) {
      q = q->next;
    }
    // now loop, if q and p hit, that must be the entry
    while (p != q) {
      p = p->next;
      q = q->next;
    }
    return p;
  }
};
