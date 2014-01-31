#include "iostream"

class Solution {
public:
  ListNode *insertionSortList(ListNode *head) {
    if (head == NULL) {
      return head;
    }
    ListNode *p = head->next;
    head->next = NULL;
    while(p != NULL) {
      if (p->val <= head->val) {
	ListNode *t = p->next;
	p->next = head;
	head = p;
	p = t;
      } else {
	ListNode *q = head;
	while(q->next != NULL && q->next->val < p->val) {
	  q = q->next;
	}
	ListNode *t = p->next;
	p->next = q->next;
	q->next = p;
	p = t;
      }
    }
    return head;
  }
};
