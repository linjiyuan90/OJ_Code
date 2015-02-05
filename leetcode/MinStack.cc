

class MinStack {
  stack<int> ele_;
  // min element and its index
  stack<pair<int, int>> minEle_;
public:
  void push(int x) {
    ele_.push(x);
    if (minEle_.empty() || minEle_.top().first > x) {
      minEle_.push({x, ele_.size()});
    }
  }

  void pop() {
    ele_.pop();
    if (ele_.size() < minEle_.top().second) {
      minEle_.pop();
    }
  }

  int top() {
    return ele_.top();
  }

  int getMin() {
    return minEle_.top().first;
  }
};


// another solution is to push x if x <= minEle_.top()
// then when poping, if ele_.top() == minEle_.top(), pop minEle_ as well
