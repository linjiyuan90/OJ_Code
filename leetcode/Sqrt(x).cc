class Solution {
public:
  int sqrt(int x) {
    if (x == 0) {
      return 0;
    }
    int low = 1, high = x;
    while(low < high) {
      int mid = (low + high) / 2;
      // mid+1, not mid
      // for example, x = 2
      if ((mid+1) <= x / (mid+1)) {
	low = mid + 1;
      } else {
	high = mid;
      }
    }
    return low;
  }
};
