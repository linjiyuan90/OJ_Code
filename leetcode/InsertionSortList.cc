/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  ListNode* insertionSortList(ListNode* head) {
    ListNode* dummy = new ListNode(0);
    for (ListNode* next; head != NULL; head = next) {
      next = head->next;
      ListNode* p = dummy;
      while(p->next != NULL && p->next->val <= head->val) {
	p = p->next;
      }
      head->next = p->next;
      p->next = head;
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
};
