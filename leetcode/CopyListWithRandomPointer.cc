class Solution {
public:
  // the cool idea is to duplicate the node
  // then seperate it
  // 1->2->3
  // 1->1'->2->2'->3->3'
  RandomListNode *copyRandomList(RandomListNode *head) {
    for (RandomListNode *p = head; p; ) {
      RandomListNode *q = new RandomListNode(p->label);
      q->next = p->next;
      p->next = q;
      p = q->next;
    }
    // copy the random pointer
    for (RandomListNode *p = head; p; p = p->next->next) {
      if (p->random != NULL) {
	p->next->random = p->random->next;
      }
    }
    // seperate the list
    RandomListNode *copy_head = NULL;
    for (RandomListNode *p = head, *q; p; ) {
      if (copy_head == NULL) {
	q = copy_head = p->next;
	p->next = q->next;
	p = p->next;
      } else{
	q->next = p->next;
	q = p->next;
	p->next = q->next;
	p = p->next;
      }
    }
    return copy_head;
  }
};
