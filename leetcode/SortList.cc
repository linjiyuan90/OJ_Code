#include "iostream"


struct ListNode {
  int val;
  ListNode *next;
  ListNode (int x) : val(x), next(NULL) {}
};

// Any better way?
class Solution {
public:
  ListNode *sortList(ListNode *head) {
    if (head == NULL || head->next == NULL) {
      return head;
    }
    int n = 0;
    for (ListNode *p = head; p != NULL; p = p->next) {
      ++n;
    }
    n /= 2;
    ListNode *p = head;
    while (n > 1) {
      --n;
      p = p->next;
    }
    ListNode *right = sortList(p->next);
    p->next = NULL;
    ListNode *left = sortList(head);
    head = p = NULL;
    while (left != NULL && right != NULL) {
      if (left->val < right->val) {
	if (p == NULL) {
	  head = p = left;
	} else {
	  p->next = left;
	  p = p->next;
	}
	left = left->next;
      } else {
	if (p == NULL) {
	  head = p = right;
	} else {
	  p->next = right;
	  p = p->next;
	}
	right = right->next;
      }
    }
    if (left == NULL) {
      p->next = right;
    } else {
      p->next= left;
    }
    return head;
  }
};

int main() {
  Solution sol;
  ListNode *head = new ListNode(1);
  head = sol.sortList(head);
  while (head != NULL) {
    std::cout << head->val << " ";
    head = head->next;
  }
  std::cout << std::endl;
  
  return 0;
}
