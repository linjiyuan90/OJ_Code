/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
  // start from 0
  ListNode* nthNode(ListNode* head, int n) {
    while(head != NULL && n--) {
      head = head->next;
    }
    return head;
  }
  ListNode* reverseList(ListNode* head) {
    ListNode* dummy = new ListNode(0);
    ListNode* pre = dummy;
    for (; head != NULL;) {
      ListNode* next = head->next;
      head->next = pre->next;
      pre->next = head;
      head = next;
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
  int listLen(ListNode* head) {
    int len = 0;
    for (;head != NULL; head = head->next) {
      ++ len;
    }
    return len;
  }
  ListNode* merge(ListNode* left, ListNode* right) {
    ListNode* dummy = new ListNode(0);
    ListNode* head = dummy;
    for(; left != NULL && right != NULL; ) {
      head->next = left;
      left = left->next;
      head->next->next = right;
      right = right->next;
      head = head->next->next;
    }
    if (left != NULL) {
      head->next = left;
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
public:
  void reorderList(ListNode *head) {
    if (head == NULL) {
      return;
    }
    int n = listLen(head);
    ListNode* left = nthNode(head, n/2);
    ListNode* right = reverseList(left->next);
    left->next = NULL;
    left = head;
    head = merge(left, right);
  }
};
