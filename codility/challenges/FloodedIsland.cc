/*
  Query at each level, how many segments that is > l
  Simulate from high level to low level, new or connect

  The official solution is more clear:
  A position j is the right side of an island only if:
  1) Aj > Aj+1, or j = N-1
  2) the water level is below Aj, but not below Aj+1
  So for every position j, such that Aj > Aj+1 (or j = N-1), when the water level falls below
  Aj the number of islands +1, but when it falls below Aj+1, -1.
*/

#include "algorithm"

vector<int> solution(vector<int> &A, vector<int> &B) {
  // just simulate from high level to low level
  int n = A.size();
  int m = B.size();
  int max_a = *max_element(A.begin(), A.end());
  int max_b = *max_element(B.begin(), B.end());
  std::vector<std::vector<int>> plots(max_a + 1);
  for (int i = 0; i < n; ++i) {
    plots[A[i]].push_back(i);
  }
  int max = std::max(max_a, max_b);
  std::vector<int> islands(max+1);
  // decreasing level
  for (int l = max - 1; l >= 0; --l) {
    islands[l] = islands[l+1];
    if (l < max_a) {
      for (auto& p : plots[l+1]) {
	// new one
	if (p == 0 || A[p-1] <= l) {
	  ++ islands[l];
	} 
	// connect to the following one
	if (p < n - 1 && A[p+1] > l+1) {
	  -- islands[l];
	}
      }
    }
  }
  std::vector<int> res(m);
  for (int i = 0; i < m; ++i) {
    res[i] = islands[B[i]];
  }
  return res;
}

vector<int> solution(vector<int> &A, vector<int> &B) {
  int n = A.size(), m = B.size();
  int max_a = *max_element(A.begin(), A.end());
  int max_b = *max_element(B.begin(), B.end());
  int max = std::max(max_a, max_b);
  std::vector<int> islands(max+2);
  for (int i = 1; i < n; ++i) {
    if (A[i-1] > A[i]) {
      ++ islands[A[i-1]];
      -- islands[A[i]];
    }
  }
  ++ islands[A[n-1]];
  std::partial_sum(islands.rbegin(), islands.rend(), islands.rbegin());
  std::vector<int> res(m);
  for (int i = 0; i < m; ++i) {
    res[i] = islands[B[i]+1];
  }
  return res;
}
