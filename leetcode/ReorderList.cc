#include "iostream"

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int val): val(val), next(NULL) {}
  ListNode(int val, ListNode *next): val(val), next(next) {}
};

class Solution {
public:
  void reorderList(ListNode *head) {
    int len = 0;
    for (ListNode *p = head; p; p = p->next) {
      ++len;
    }
    if (len <= 1) {
      return;
    }
    int cnt = 0;
    ListNode *p = NULL, *q = NULL;
    for (p = head; p; p = p->next) {
      if(++cnt == (len+1) / 2) {
	q = p->next;
	p->next = NULL;
	p = NULL;
	// reverse the tailing list
	while (q != NULL) {
	  ListNode *t = q->next;
	  q->next = p;
	  p = q;
	  q = t;
	}
	break;
      }
    }
    // now p holds the reversed tailing list
    // combine two lists q, p
    for (q = head; q != NULL && p != NULL; ) {
      ListNode *pn = p->next, *qn = q->next;
      q->next = p;
      p->next = qn;
      q = qn;
      p = pn;
    }
  }
};

int main() {
  Solution sol;
  ListNode *head = new ListNode(5);
  head = new ListNode(4, head);
  head = new ListNode(3, head);
  head = new ListNode(2, head);
  head = new ListNode(1, head);
  for (ListNode *p = head; p != NULL; p = p->next) {
    std::cout << p->val << " ";
  }
  std::cout << std::endl;
  sol.reorderList(head);
  for (ListNode *p = head; p != NULL; p = p->next) {
    std::cout << p->val << " ";
  }
  std::cout << std::endl;
  return 0;
}
