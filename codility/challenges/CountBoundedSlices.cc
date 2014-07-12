#include "deque"

// ***
// Calculate the number of slices in which (maximum - minimum <= K).
//
// First, this is a counting problem
// loop each element, when at ix, find min{x}, 
// where x <= ix and max{A[x..ix]} - min{A[x..ix]} <= K
// Then add (ix - x + 1) to the answer.

// With respect to the `find` operation,
// maintain two monotonical deque, one descending, one ascending
// Take the descending one as example, when at ix, elements in the
// descending deque satisfy: A[x1] > A[x2] > ... > A[ix], x1 < x2 < ... < ix
// When at ix, pop front the two deques until 
//   A[desc.front()] - A[asec.front()] <= K (suppose the deques store index)
// However, min(desc.front(), asce.front()) may no be the min{x} as defined before.
// For each elements d_i in descending deque, we need to record min{dx} where 
//  A[min{dx}..d_i] <= A[d_i]
// Actually, min{dx} = d_(i-1) + 1
// As the same way, we need to record min{ax} for each elemetns a_i in ascending deque.
// 
// The expected min{x} = min{min{dx}, min{ax}}

int solution(int K, vector<int> &A) {
  int res = 0;
  // (i, first index >/< than A[i])
  std::deque<std::pair<int, int>> desc, asc;
  for (int i = 0, n = A.size(); i < n; ++i) {
    int pre = i;
    while (!desc.empty() && A[desc.back().first] <= A[i]) {
      pre = desc.back().second;
      desc.pop_back();
    }
    desc.push_back({i, pre});
    pre = i;
    while (!asc.empty() && A[asc.back().first] >= A[i]) {
      pre = asc.back().second;
      asc.pop_back();
    }
    asc.push_back({i, pre});
    // pop front until max - min <= K
    while (A[desc.front().first] - A[asc.front().first] > K) {
      if (desc.front().first < asc.front().first) {
	asc.front().second = std::max(asc.front().second, desc.front().first + 1);
	desc.pop_front();
      } else {
	desc.front().second = std::max(desc.front().second, asc.front().first + 1);
	asc.pop_front();
      }
    }
    res += i - std::min(desc.front().second, asc.front().second) + 1;
    if (res > 1000000000) {
      return 1000000000;
    }
  }
  return res;
}

// O(nlogn)
// notice that if the slice (i, j) is bounded then every slice (i+1, j), (i+2, j), ..., (j, j)
// is bounded too. There is no need to check index j from the begining.
// j = 0
// for i <- 0 until n
//   while(j < n && minMaxQuery(i, j) <= K) ++j
//   res += (j - i)
//
// Use Interval Tree to make minMaxQuery works in O(logn)
