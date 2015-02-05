/*
  When duplicate values are allowed, pop back until front != back.
  Then do the normal binary search
*/
class Solution {
public:
  bool search(int A[], int n, int target) {
    int low = 0, high = n - 1;
    while(low < high && A[low] == A[high]) {
      --high;
    }
    while(low < high) {
      int mid = (low + high) / 2;
      if (A[mid] > A[high]) { // left part
	if (target > A[mid] || target < A[low]) {
	  low = mid + 1;
	} else {
	  high = mid;
	}
      } else {
	if (target <= A[mid] || target > A[high]) {
	  high = mid;
	} else {
	  low = mid + 1;
	}
      }
    }
    return A[low] == target ? true : false;
  }
};
