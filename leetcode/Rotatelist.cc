#include "iostream"

class Solution {
public:
  // Note the case when k >= len
  ListNode *rotateRight(ListNode *head, int k) {
    if (head == NULL) {
      return head;
    }
    ListNode *p = head, *q;
    int n = 0;
    while (p != NULL) {
      ++ n;
      p = p->next;
    }
    k %= n;
    q = p = head;
    while (p->next != NULL) {
      p = p->next;
      if (k == 0) {
	q = q->next;
      } else {
	--k;
      }
    }
    p->next = head;
    head = q->next;
    q->next = NULL;
    return head;
  }
};

/*
  {1} 0
  {1, 2} 2
*/
