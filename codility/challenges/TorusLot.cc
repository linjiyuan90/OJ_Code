/*
  Find max submatrix sum, where the matrix is a ball, not planar.
  
  Enumerate columns, then calculate max sum in a cycle
*/

#include "numeric"
#include "algorithm"

int solution(const vector<vector<int>> &C) {
  if (C.empty()) {
    return 0;
  }
  int n = C.size(), m = C.front().size();
  std::vector<std::vector<int>> row_sum(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
    std::partial_sum(C[i].begin(), C[i].end(), row_sum[i].begin());
  }
  int res = 0;
  // enumerate columns (a, b)
  for (int a = 0; a < m; ++a) {
    for (int b = a; b < a + m; ++b) {
      std::vector<int> arr(n);
      for (int i = 0; i < n; ++i) {
	arr[i] = (b < m ? row_sum[i][b] : row_sum[i][b%m] + row_sum[i][m-1]) 
	  - (a == 0 ? 0 : row_sum[i][a-1]);
      }
      // find max/min sum
      int max = arr[0];
      int min = arr[0];
      for (int i = 0, j = 0, max_sum = 0, min_sum = 0; i < n; ++i) {
	max = std::max(max, std::max(0, max_sum) + arr[i]);
	min = std::min(min, std::min(0, min_sum) + arr[i]);
	max_sum = std::max(arr[i], max_sum + arr[i]);
	min_sum = std::min(arr[i], min_sum + arr[i]);
      }
      res = std::max(res, max);
      res = std::max(res, std::accumulate(arr.begin(), arr.end(), 0) - min);
    }
  }
  return res;
}
