

class Solution {
public:
  ListNode *detectCycle(ListNode *head) {
    // two pointers 
    // once know there is a cycle
    // loop again to get cycle length n
    // then enumerate each node
    int n = 0;
    ListNode *a = head, *b = head;
    while (a != NULL && b != NULL) {
      a = a->next;
      b = b->next;
      if (b != NULL) {
	b = b->next;
	// find a loop and figure out its length
	if (a == b) {
	  n = 1;
	  for (b = b->next; a != b; b = b->next) {
	    ++n;
	  }
	  // start from head
	  // enumerate every node to find the entry of the cycle
	  for (a = b = head; n--; b = b->next);
	  while (true) {
	    if (a == b) {
	      return a;
	    }
	    a = a->next;
	    b = b->next;
	  }
	}
      }
    }
    return NULL;
  }
};
