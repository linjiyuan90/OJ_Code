// if duplicates are allowed
// the trick is that the head of A may be equal to tail of A
// which lead to failure of the search_gap program
// just remove the tail which equals to head <--
// Learn from 
// https://github.com/Dionysus1227/edocteel/blob/master/Search%20in%20Rotated%20Sorted%20Array%20II.cc
class Solution {
public:
  bool search(int A[], int n, int target) {
    // remove tail which equal to head
    while (n > 1 && A[n-1] == A[0]) {
      -- n;
    }
    // first search the minimum element (the gap)
    int gap = search_gap(A, n);
    int *p = std::lower_bound(A, A + gap, target);
    if (p != A + gap && *p == target) {
      return true;
    }
    p = std::lower_bound(A + gap, A + n, target);
    if (p != A + n && *p == target) {
      return true;
    }
    return false;
  }

private:
  int search_gap(int A[], int n) {
    int lo = 0, hi = n-1;
    while (lo < hi) {
      int m = (lo + hi) / 2;
      if (A[m] > A[hi]) {
	lo = m + 1;
      } else {
	hi = m;
      }
    }
    return lo;
  }
};

// [3, 1, 1]
// [1, 1, 1, 3, 1]
