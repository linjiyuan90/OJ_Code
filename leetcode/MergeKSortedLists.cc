/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
  struct ListNodeCmp {
    bool operator()(const ListNode* a, const ListNode* b) {
      return a->val > b->val;
    }
  };
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    std::priority_queue<ListNode*, std::vector<ListNode*>, ListNodeCmp> pq;
    for (auto& list : lists) {
      if (list != NULL) {
        pq.push(list);
      }
    }
    ListNode* dummy = new ListNode(0);
    ListNode* head = dummy;
    while (!pq.empty()) {
      ListNode* top = pq.top();
      pq.pop();
      head->next = top;
      head = head->next;
      if (top->next != NULL) {
        pq.push(top->next);
      }
    }
    head = dummy->next;
    delete dummy;
    return head;
  }
};
