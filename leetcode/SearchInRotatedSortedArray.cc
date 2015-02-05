/*
  instead of find the pivot first, find the target directly by discussing whether
  the mid is left part or right part.
*/

class Solution {
public:
  int search(int A[], int n, int target) {
    int low = 0, high = n-1;
    while(low < high) {
      int mid = (low + high) / 2;
      if (A[mid] > A[high]) {  // mid is in the left part
	if (target > A[mid] || target < A[low]) {
	  low = mid + 1;
	} else {
	  high = mid;
	}
      } else {
	if (target > A[high] || target <= A[mid]) {
	  high = mid;
	} else {
	  low = mid + 1;
	}
      }
    }
    return A[low] == target ? low : -1;
  }
};
