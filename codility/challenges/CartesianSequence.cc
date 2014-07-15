/*
  Given a sequence, find the longest path that is decreasing and elements between
  (A[B[i]], A[B[i+1]]) must less than min{A[B[i]], A[B[i+1]]}

  After some simulation, we'll find that this is in fact a tree!  
  For segment [i, j], the root is at the maximal value k, the left child of [i,
  k) is the max{[i, k)}, the right child of (k, j] is max{(k, j]}. Nice!
  
  If we build this tree, (official solution says this is a Cartesian Tree), then
  the answer is the longest path~
  
  We can maintain a decreasing stack, when a new element come in, check top of
  the stack and decide which is its parent (the smaller one).
*/

#include "stack"
#include "algorithm"

int solution(const vector<int> &A) {
  int n = A.size();
  // maintain a decreasing sequence
  std::stack<int> stk;
  std::vector<int> dp(n, 1);
  for (int i = 0; i < n; ++i) {
    while(!stk.empty() && A[stk.top()] < A[i]) {
      int t = stk.top();
      stk.pop();
      if (stk.empty() || A[stk.top()] > A[i]) {
	dp[i] = std::max(dp[i], dp[t] + 1);
      } else {
	dp[stk.top()] = std::max(dp[stk.top()], dp[t] + 1);
      }
    }
    stk.push(i);
  }
  while(stk.size() > 1) {
    int t = stk.top();
    stk.pop();
    dp[stk.top()] = std::max(dp[stk.top()], dp[t] + 1);
  }
  return *std::max_element(dp.begin(), dp.end());
}
