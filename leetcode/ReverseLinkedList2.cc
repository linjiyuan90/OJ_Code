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
  ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode* dummy = new ListNode(0);
    ListNode* pre = dummy;
    pre->next = head;
    ListNode* mthNode;
    for (int nth = 0; nth < n; ++nth) {
      if (nth == m - 1) {
	mthNode = head;
      }
      ListNode* next = head->next;
      if (nth >= m - 1) {
	head->next = pre->next;
	pre->next = head;
      } else {
	pre = head;
      }
      head = next;
    }
    mthNode->next = head;
    head = dummy->next;
    delete dummy;
    return head;
  }
};
