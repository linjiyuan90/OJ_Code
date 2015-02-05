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
  ListNode *partition(ListNode *head, int x) {
    ListNode *lt = new ListNode(-1), *ge = new ListNode(-1);
    ListNode *p = lt, *q = ge;
    for (; head != NULL; head = head->next) {
      if (head->val < x) {
	p->next = head;
	p = p->next;
      } else {
	q->next = head;
	q = q->next;
      }
    }
    p->next = ge->next;
    q->next = NULL;
    head = lt->next;
    delete lt;
    delete ge;
    return head;
  }
};
