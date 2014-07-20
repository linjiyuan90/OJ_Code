#include "stack"

template<typename InputIter, typename OutputIter>
void closest_ascender(InputIter beg, InputIter end, OutputIter res) {
  // maintain a decreasing stack
  std::stack<InputIter> stk; 
  for (; beg < end; ++beg, ++res) {
    while(!stk.empty() && *(stk.top()) <= *beg) {
      stk.pop();
    }
    if (!stk.empty() && (*res == 0 || beg - stk.top() < *res)) {
      *res = beg - stk.top();
    }
    stk.push(beg);
  }
}

vector<int> solution(const vector<int> &A) {
  std::vector<int> res(A.size());
  closest_ascender(A.begin(), A.end(), res.begin());
  closest_ascender(A.rbegin(), A.rend(), res.rbegin());
  return res;
}
