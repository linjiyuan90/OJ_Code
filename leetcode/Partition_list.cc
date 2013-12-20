#include "iostream"

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x): val(x), next(NULL) {}
};

class Solution {
public:
  ListNode *partition(ListNode *head, int x) {
    // Can't define like, for reason "taking adderss of temporary"
    // ListNode *lt_node = &ListNode(0);
    ListNode lt_node = ListNode(0), gt_node = ListNode(0);
    ListNode *lt = &lt_node, *gt = &gt_node;
    for (ListNode *p = head; p != NULL; p = p-> next) {
      if (p->val >= x) {
        gt -> next = p;
        gt = p;
      } else {
	// last node with value < x
	lt -> next = p;
        lt = p;
      }
    }
    gt -> next = NULL;
    lt -> next = gt_node.next;
    return lt_node.next;
  }
};
