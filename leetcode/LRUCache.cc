#include "iostream"
#include "unordered_map"
#include "list"

// The O(1) solution should be:
// ArrayList + HashMap

// Java has LinkedHashMap can be used to implement the LRU Cache
// http://dncroot.com/2007/09/18/lru-caches/

class LRUCache {
public:
  LRUCache(int capacity) {
    this->capacity = capacity;
    // dummy node
    tail = head = new ListNode();
  }
  
  int get(int key) {
    auto it = kv.find(key);
    if (it == kv.end()) {
      return -1;
    } else {
      update(key);
      return it->second->val;
    }
  }

  void set(int key, int value) {
    if (this->capacity == 0) {
      return;
    }
    // insert
    if (kv.count(key) == 0) {
      tail->next = new ListNode(key, value, tail, NULL);
      tail = tail->next;
      kv[key] = tail;
      if (kv.size() > this->capacity) {
	ListNode *first = head->next;
	first->next->prev = head;
	head->next = first->next;
	kv.erase(first->key);
	delete first;
      }
    } else {
      // update
      kv[key]->val = value;
      update(key);
    }
  }

private:
  struct ListNode {
    int key, val;
    ListNode *next, *prev;
    // delegation
    ListNode(): ListNode(0, 0, NULL, NULL) {}
    ListNode(int key, int val, ListNode *prev, ListNode *next):
      key(key), val(val), prev(prev), next(next) {}
  };

  ListNode *head, *tail;
  std::unordered_map<int, ListNode*> kv;
  int capacity;

  // assume key exists in kv
  void update(int key) {
    ListNode *pl = kv[key];
    if (pl != tail) {
      pl->prev->next = pl->next;
      pl->next->prev = pl->prev;
      tail->next = pl;
      pl->prev = tail;
      pl->next = NULL;
      tail = pl;
    }
  }
};

int main() {
  LRUCache cache(3);
  std::cout << cache.get(1) << std::endl;
  cache.set(1, 1);
  cache.set(2, 2);
  cache.set(3, 3);
  cache.set(4, 4);
  std::cout << cache.get(4) << std::endl;
  std::cout << cache.get(3) << std::endl;
  std::cout << cache.get(2) << std::endl;
  std::cout << cache.get(1) << std::endl;
  return 0;
}
