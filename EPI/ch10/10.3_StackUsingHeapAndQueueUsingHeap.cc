/*
  Implement a Stack API using a heap and a queue API using a heap

  The nice thing is that it inherits priority_queue's methods!
*/

#include "iostream"
#include "queue"
#include "vector"

using namespace std;

template<typename T>
class Compare {
public:
  bool operator()(const pair<int, T>& lhs, const pair<int, T>& rhs) const {
    return lhs.first < rhs.first;
  }
};

template<typename T>
class Stack: // inherits empty(), pop(), and size() methods
  public priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> {
  
 private:
  int order;
  typedef priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> PQ;
  
 public:
  Stack(): order(0) {}
  
  // why make the return value of top const?
  const T& top() const {
    return PQ::top().second;
  }
  
  void push(const T& x) {
    PQ::emplace(order++, x);
  }
};

template<typename T>
class Queue:
  public priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> {
 private:
  int order;
  typedef priority_queue<pair<int, T>, vector<pair<int, T>>, Compare<T>> PQ;

 public:
  Queue(): order(0) {}

  const T& front() const {
    return PQ::top().second;
  }
  void push(const T& x) {
    PQ::emplace(order--, x);
  }
};

void testStack() {
  Stack<int> stk;
  stk.push(3);
  stk.push(2);
  cout << stk.size() << " " << stk.top() << std::endl;
  stk.pop();
  cout << stk.size() << " " << stk.top() << std::endl;
  stk.push(1);
  cout << stk.size() << " " << stk.top() << std::endl;  
}

void testQueue() {
  Queue<int> qe;
  qe.push(3);
  qe.push(2);
  cout << qe.size() << " " << qe.front() << std::endl;
  qe.pop();
  cout << qe.size() << " " << qe.front() << std::endl;
  qe.push(1);
  cout << qe.size() << " " << qe.front() << std::endl;
}

int main() {
  testStack();
  testQueue();
  return 0;
}
