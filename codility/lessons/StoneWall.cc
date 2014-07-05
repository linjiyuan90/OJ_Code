#include "stack"

int solution(const vector<int> &H) {
  // maintain a montonously increasing stack
  int res = 0;
  std::stack<int> blocks;
  for (auto& h : H) {
    while (!blocks.empty() && blocks.top() > h) {
      blocks.pop();
    }
    // if there is no blocks that has same height with h, needs a new one
    if (blocks.empty() || blocks.top() < h) {
      blocks.push(h);
      ++ res;
    }
  }
  return res;
}
