// The O(1) solution should be:
// ArrayList + HashMap

// Java has LinkedHashMap can be used to implement the LRU Cache
// http://dncroot.com/2007/09/18/lru-caches/

class LRUCache {
public:
  LRUCache(int capacity) {
    this->capacity = capacity;
  }
  
  int get(int key) {
    if (hash.count(key)) {
      move_to_front(key);
      return hash[key]->second;
    }
    return -1;
  }

  void set(int key, int  value) {
    if (capacity == 0) {
      return;
    }
    if (hash.count(key)) {
      hash[key]->second = value;
      move_to_front(key);
    } else {
      data.emplace_front(key, value);
      hash[key] = data.begin();
      if (data.size() > capacity) {
	hash.erase(data.back().first);
	data.pop_back();
      }
    }
  }

  void erase(int key) {
    if(hash.count(key)) {
      data.erase(hash[key]);
      hash.erase(key);
    }
  }

private:
  int capacity;
  // [(key, value)]
  typedef std::list<std::pair<int, int>> Cache;
  Cache data;
  std::unordered_map<int, Cache::iterator> hash;

  void move_to_front(int key) {    
    data.emplace_front(key, hash[key]->second);
    data.erase(hash[key]);
    hash[key] = data.begin();
  }
};


class LRUCache {
public:
  LRUCache(int capacity) {
    this->capacity = capacity;
    tail = head = new Node(0, 0);
  }
  
  int get(int key) {
    if (hash.count(key)) {
      Node *node =  hash[key];
      update(node);
      return node->val;
    }
    return -1;
  }

  void set(int key, int value) {
    if (capacity == 0) {
      return;
    }
    if (hash.count(key)) {
      Node *node = hash[key];
      node->val = value;
      update(node);
    } else {
      hash[key] = tail->next = new Node(key, value, tail, NULL);
      tail = tail->next;
      // remove the oldest
      if (hash.size() > capacity) {
	Node *t = head->next;
	hash.erase(t->key);
	t->next->prev = head;
	head->next = t->next;
	delete t;
      }
    }
  }

  ~LRUCache() {
    delete head;
    for (auto &e : hash) {
      delete e.second;
    }
  }

private:  
  struct Node {
    int key, val;
    Node *prev, *next;

    Node(int key, int val) {
      Node(key, val, NULL, NULL);
    }
    Node(int key, int val, Node* prev, Node *next): 
      key(key), val(val), prev(prev), next(next) {
    }
  };

  // capacity
  int capacity;
  // lookup Node with key
  std::unordered_map<int, Node*> hash;
  // dummy node
  Node *head, *tail;

  void update(Node *node) {
    if (node != tail) {
      node->prev->next = node->next;
      node->next->prev = node->prev;
      node->next = NULL;
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
  }
};

