/*
  Find max Q - P, where A[P] <= A[Q], 0 <= P <= Q < N
  
  O(nlogn)
  Maintain a pre_min array, then do binary search.
  Another approach is sort by A[i], start from smallest value, and record the min position

  O(n)
  First, maintain a decreasing stack, since smaller and lefter values are prefered.
  Then, scan from right to left, larger and righter values are prefered.
  Pop the stack till the top value > current value.
*/

#include "algorithm"
#include "iterator"
#include "stack"

int solution(vector<int>& A) {
  int n = A.size();
  // first, maintain a decreasing stack
  std::stack<int> desc;
  for (int i = 0; i < n; ++i) {
    if (desc.empty() || A[desc.top()] > A[i]) {
      desc.push(i);
    }
  }
  // scan from right to left and pop_back of the stack
  int res = 0;
  for (int i = n - 1; i >= 0; --i) {
    while(!desc.empty() && A[desc.top()] <= A[i]) {
      res = std::max(res, i - desc.top());
      desc.pop();
    }
  }
  return res;
}

int solution(vector<int>& A) {
  std::vector<int> pre_min;
  std::partial_sum(A.begin(), 
		   A.end(), 
		   std::back_inserter(pre_min),
		   [](const int& a, const int& b){
		     return std::min(a, b);
		   });
  int n = A.size();
  int res = 0;
  for (int i = 0; i < n; ++i) {
    // find the first one <= A[i] in left side
    auto it = std::lower_bound(pre_min.begin(), 
			       pre_min.begin() + i,
			       A[i],
			       std::greater<int>());
    int j = it - pre_min.begin();
    res = std::max(res, i - j);
  }
  return res;
}

int solution(vector<int>& A) {
  int n = A.size();
  std::vector<std::pair<int, int>> values(n);
  for (int i = 0; i < n; ++i) {
    values[i] = {A[i], i};
  }
  std::sort(values.begin(), values.end());
  int res = 0;
  int min_ix = n;
  for (int i = 0; i < n; ++i) {
    min_ix = std::min(min_ix, values[i].second);
    res = std::max(res, values[i].second - min_ix);
  }
  return res;
}
