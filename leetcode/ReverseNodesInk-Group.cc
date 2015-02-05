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
  ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode* dummy = new ListNode(0);
    ListNode* pre = dummy;
    int cnt = 0;
    for (ListNode* start; head != NULL; ) {
      if (cnt == 0) {  // record start of the original group
	start = head;
      }
      ListNode* next = head->next;
      head->next = pre->next;
      pre->next = head;
      if (++cnt == k) {
	pre = start;
	cnt = 0;
      }
      head = next;
    }
    // reverse the remaining part start from pre->next
    if (cnt != 0) {
      head = pre->next;
      pre->next = NULL;
      for (; head != NULL; ) {
	ListNode* next = head->next;
	head->next = pre->next;
	pre->next = head;
	head = next;
      }
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
};
