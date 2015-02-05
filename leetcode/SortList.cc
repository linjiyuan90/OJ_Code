
class Solution {
public:
  // quick sort
  ListNode *sortList(ListNode *head) {
    if (head == NULL || head->next == NULL) {
      return head;
    }
    ListNode *ltDummy = new ListNode(-1);
    ListNode *eqDummy = new ListNode(-1);
    ListNode *gtDummy = new ListNode(-1);
    ListNode *lt = ltDummy;
    // need to record equal!
    ListNode *eq = eqDummy;
    ListNode *gt = gtDummy;
    int pivot = head->val;
    for (ListNode *p = head; p != NULL; p = p->next) {
      if (p->val < pivot) {
	lt->next = p;
	lt = lt->next;
      } else if (p->val == pivot) {
	eq->next = p;
	eq = eq->next;
      } else {
	gt->next = p;
	gt = gt->next;
      }
    }
    lt->next = NULL;
    eq->next = NULL;
    gt->next = NULL;
    ltDummy->next = sortList(ltDummy->next);
    gtDummy->next = sortList(gtDummy->next);
    lt = ltDummy;
    for (ListNode *p = ltDummy->next; p != NULL; p = p->next) {
      lt = p;
    }
    lt->next = eqDummy->next;
    eq = eqDummy;
    for (ListNode *p = eqDummy->next; p != NULL; p = p->next) {
      eq = p;
    }
    eq->next = gtDummy->next;
    head = ltDummy->next;
    delete ltDummy;
    delete eqDummy;
    delete gtDummy;
    return head;
  }
};
