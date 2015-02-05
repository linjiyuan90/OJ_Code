class LRUCache{
  typedef std::pair<int, int> Node;
  typedef std::list<Node>::iterator NodePtr;
    
  std::list<Node> lists;
  std::unordered_map<int, NodePtr> hash;
  int _capacity;
    
public:
  LRUCache(int capacity) {
    if (capacity < 1) {
      throw std::runtime_error("Capacity <= 0");
    }
    _capacity = capacity;
  }
    
  int get(int key) {
    if (!hash.count(key)) {
      return -1;
    }
    NodePtr it = hash[key];
    lists.splice(lists.begin(), lists, it);
    return it->second;
  }
    
  void set(int key, int value) {
    if (hash.count(key)) {
      NodePtr it = hash[key];
      it->second = value;
      lists.splice(lists.begin(), lists, it);
    } else {
      if (lists.size() < _capacity) {
	lists.insert(lists.begin(), Node(key, value));
	hash[key] = lists.begin();
      } else {
	hash.erase(lists.back().first);
	lists.back() = {key, value};
	lists.splice(lists.begin(), lists, --lists.end());
	hash[key] = lists.begin();
      }
    }
  }
};
