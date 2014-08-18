/*
  Find the minimum number of adjacent swaps that make the sequence *up and down*

  To make the sequence sorted, the number of swaps will be inverse pairs.
  When regrading to *up and down*
  For each a[i], it has 2 choices:
  if a[i] will be assigned to left side, then it needs to swap #{A[j]}, A[j] > A[i], j < i
  if a[i] will be assigned to right side, 

  Conclusion:
  Only count #{A[j]}, that A[i] < A[j]

  The official solution is at each time, find the smallest elements, then choose to place it 
  to the end has less swaps. So, it becomes a subproblem.
  This enlight me that: if it's hard to know where to start, try the minimum/maximum one first!
*/

#include "iostream"
#include "vector"
#include "algorithm"
#include "functional"

int solveByCount(const std::vector<int>& A) {
  int ans = 0;
  for (int i = 0, n = A.size(); i < n; ++i) {
    int left = std::count_if(A.begin(), A.begin() + i, std::bind1st(std::less<int>(), A[i]));
    int right = std::count_if(A.begin()+i+1, A.end(), std::bind1st(std::less<int>(), A[i]));
    ans += std::min(left, right);
  }
  return ans;
}

int solveByChoosingMin(const std::vector<int>& A) {
  auto AA = A;
  auto beg = AA.begin(), end = AA.end();
  int ans = 0;
  for (int i = 0, n = AA.size(); i < n-1; ++i) {
    auto minIt = std::min_element(beg, end);
    int left = std::count_if(beg, minIt, std::bind1st(std::less<int>(), *minIt));
    int right = std::count_if(minIt+1, end, std::bind1st(std::less<int>(), *minIt));
    if (left < right) {
      std::rotate(beg, minIt, minIt+1);
      ++ beg;
    } else {
      std::rotate(minIt, minIt+1, end);
      -- end;
    }
    ans += std::min(left, right);
  }
  return ans;
}

int main() {
  int T, n, t = 1;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n;
    std::vector<int> A(n);
    for (auto& a : A) {
      std::cin >> a;
    }
    std::cout << solveByChoosingMin(A) << std::endl;
  }
  return 0;
}
