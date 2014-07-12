#include "algorithm"

int solution(int K, int M, vector<int> &A) {
  int n = A.size();
  int low = *max_element(A.begin(), A.end()), high = M * n + 1;
  while (low < high) {
    int mid = (low + high) / 2;
    // try to pack
    int k = 1, sum = 0;  // note initially k is 1
    for (int i = 0; i < n; ++i) {
      if (sum + A[i] > mid) {  // new a block
	++ k;
	sum = 0;
      }
      sum += A[i];
    }
    if (k <= K) { // ok
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return low;
}
