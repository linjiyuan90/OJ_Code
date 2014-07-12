/*
  Find the maximum number of flags that can be set on mountain peaks.
  Constraint is that, if k flags are choosen, then distance between flags must >= k
  
  My native algorithm is to binary search.

  https://codility.com/media/train/solution-flags.pdf
  Maintain a array, next[i] which records peaks which position >= i
  Then enumerate k and count
  Note that k <= sqrt(n), and each count requires O(n/k)
  Total: O(n)
  Note boundary: floor(sqrt(n)) + 1
*/

#include "cmath"

#include "algorithm"
#include "numeric"

std::vector<int> nextPeak(const std::vector<int>& A) {
  int n = A.size();
  std::vector<int> next(n);
  for (int i = n - 1, last = n; i >= 0; --i) {
    // peak
    if (0 < i && i < n - 1 && A[i] > A[i-1] && A[i] > A[i+1]) {
      last = i;
    }
    next[i] = last;
  }
  return next;
}

// O(n)
int solution(std::vector<int>& A) {
  auto next = nextPeak(A);
  for (int n = A.size(), k = (int)sqrt(n) + 1; k > 0; --k) { // floor(sqrt(n)) + 1!!!
    for (int i = 0, have = 0; i < n; i += k) {
      i = next[i];
      if (i == next[i]) { // peak
	++ have;
      }
      if (have == k) {
	return k;
      }
    }
  }
  return 0;
}


// O(klogm), maybe a linear is also ok
bool check(const std::vector<int>& peaks, int k) {
  int cnt = 1;
  for (int i = 0, m = peaks.size(); i < m && cnt < k;) {
    auto it = std::lower_bound(peaks.begin(), peaks.end(), peaks[i] + k);
    if (it == peaks.end()) {
      break;
    }
    i = it - peaks.begin();
    ++ cnt;
  }
  return cnt == k;
}

// O(logn*klogm)
int solution(vector<int> &A) {
  std::vector<int> peaks;
  int n = A.size();
  for (int i = 1; i < n-1; ++i) {
    if (A[i] > A[i-1] && A[i] > A[i+1]) {
      peaks.push_back(i);
    }
  }
  int low = 0, high = n;
  while (low < high) {
    int k = (low + high) / 2;
    if (check(peaks, k)) {
      low = k + 1;
    } else {
      high = k;
    }
  }
  return peaks.empty() ? 0 : low - 1;
}
