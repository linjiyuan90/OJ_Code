/*
  solution from the web says that, only need to consider slice with len 2 and 3 ...
  
  hdu 2993
  push_back i - t
  check front, Not back!
*/

#include "limits"
#include "vector"
#include "iostream"
#include "numeric"
#include "deque"

bool is_less_equal(const std::vector<int>& sum,
		   int k,
		   int j,
		   int i) {
  return (0LL + sum[i] - sum[k]) * (i - j) <= (0LL + sum[i] - sum[j]) * (i - k);
}

int solution(std::vector<int> &A) {
  int n = A.size();
  int t = 2;
  std::vector<int> sum(n + 1);
  std::partial_sum(A.begin(), A.end(), sum.begin() + 1);
  std::deque<int> dq;
  int min_i = 0;
  int min_sum = sum[n];
  int min_len = n;
  // maintain a curve with decreasing ratio
  for (int i = t, ii = i - t; i <= n; ++i, ++ii) {
    // push ii
    while(dq.size() > 1) {
      int last = dq.back();
      dq.pop_back();
      if (!is_less_equal(sum, dq.back(), last, ii)) {
        dq.push_back(last);
        break;
      }
    }
    dq.push_back(ii);
    // pop front
    while (dq.size() > 1) {
      int first = dq.front();
      dq.pop_front();
      if (is_less_equal(sum, first, dq.front(), i)) {
        dq.push_front(first);
        break;
      }
    }
    // using divide will have problem!
    if ((sum[i] - sum[dq.front()]) * min_len < min_sum * (i - dq.front())) {
	min_sum = sum[i] - sum[dq.front()];
	min_len = i - dq.front();
	min_i = dq.front();
    }
  }
  return min_i;
}
