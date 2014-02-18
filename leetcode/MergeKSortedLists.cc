class Solution {
public:
  ListNode *mergeKLists(std::vector<ListNode *> &lists) {
    ListNode *dummy = new ListNode(0), *head = dummy;
    // multimap seems faster?
    // lambda cmp not work here --!
    std::priority_queue<ListNode *, std::vector<ListNode *>, ListNodeCMP> pq;
    for (auto list : lists) {
      if (list == NULL) {
	continue;
      }
      pq.push(list);
    }
    while (!pq.empty()) {
      auto it = pq.top();
      pq.pop();
      head->next = it;
      head = head->next;
      if (head->next != NULL) {
	pq.push(head->next);
      }
    }
    head = dummy->next;
    delete dummy;
    return head;
  }

private:
  struct ListNodeCMP {
    bool operator()(const ListNode *a, const ListNode *b) {
      return a->val > b->val;
    }
  };
};
