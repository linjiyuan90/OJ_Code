
## 10.3 Implement *stack*, *queue* API using a *heap* API
Nice inheritance.
```c++
template<typename T>
class Compare {
public:
  bool operator()(const std::pair<int, T> &lhs, const std::pair<int, T> &rhs) const {
    return lhs.first < rhs.first;
  }
};

template<typename T>
class Stack:
  // inherits empty(), pop() and size() methods, nice!
  // by default is private inheritance, need to specify as public!
 public std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, Compare<T>> {
 private:
  int order;
  typedef std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, Compare<T>> PQ;
 public:  
  Stack():order(0) {
  }
  
  const T& top() const {
    return PQ::top().second;  // note the PQ namespace!
  }
  
  void push(const T&x) {
    PQ::emplace(order++, x);
  }
};
```
