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
  ListNode *deleteDuplicates(ListNode *head) {
    if (head == NULL) {
      return NULL;
    }
    ListNode* dummy = new ListNode(head->val - 1);
    ListNode* res = dummy;
    for (ListNode* pre = dummy, *cur = head; cur != NULL; ) {
      if (pre->val != cur->val) {
        res->next = cur;
        res = res->next;
      }
      pre = cur;
      cur = cur->next;
    }
    res->next = NULL;
    head = dummy->next;
    delete dummy;
    return head;
  }
};
