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
  bool hasCycle(ListNode* head) {
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
    return p != NULL && q != NULL;
  }
};
