/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
  RandomListNode *copyRandomList(RandomListNode *head) {
    if (head == NULL) {
      return NULL;
    }
    // first duplicate nodes
    for (RandomListNode *p = head; p != NULL; ) {
      // duplicate
      RandomListNode *t = new RandomListNode(p->label);
      t->next = p->next;
      RandomListNode *q = p->next;
      p->next = t;
      p = q;
    }
    // copy the random
    for (RandomListNode *p = head, *q = p->next; p != NULL; ) {
      // correct the random pointer
      if (p->random != NULL) {
	q->random = p->random->next;
      }
      p = q->next;
      if (p != NULL) {
	q = p->next;
      }
    }
    // seperate two lists
    RandomListNode *newHead = head->next;
    for (RandomListNode *p = head, *q = newHead; p != NULL;) {
      p->next = q->next;
      p = p->next;
      if (p != NULL) {
	q->next = p->next;
	q = q->next;
      }
    }
    return newHead;
  }
};
