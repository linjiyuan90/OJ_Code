// how to achive the target of O(1) space?

#include "algorithm"

int solution(const vector<int> &A) {
  auto arr = A;  // O(n) space
  std::sort(arr.begin(), arr.end());
  int res = 0;
  for (int i = 0, n = arr.size(); i < n; ++i) {
    for (int j = i + 1, k = j + 1; k < n; ++k) {
      while (j < k && arr[i] + arr[j] <= arr[k]) {
	++j;
      }
      res += (k - j);
    }
  }
  return res;
}
