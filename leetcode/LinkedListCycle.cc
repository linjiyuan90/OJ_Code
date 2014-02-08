class Solution {
public:
  // use two pointers
  // one moves one step each time, the other moves two steps each time
  bool hasCycle(ListNode *head) {
    ListNode *a = head, *b = head;
    while (a != NULL && b != NULL) {
      a = a->next;
      b = b->next;
      if (b != NULL) {
	b = b->next;
	if (a == b) {
	  return true;
	}
      }
    }
    return false;
  }
};
