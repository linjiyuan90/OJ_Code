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
  ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* cur = dummy;
    while (l1 != NULL || l2 != NULL) {
      if (l2 == NULL || l1 != NULL && l1->val < l2->val) {
        cur->next = l1;
        cur = cur->next;
        l1 = l1->next;
      } else {
        cur->next = l2;
        cur = cur->next;
        l2 = l2->next;
      }
    }
    cur->next = NULL;
    cur = dummy->next;
    delete dummy;
    return cur;
  }
};
