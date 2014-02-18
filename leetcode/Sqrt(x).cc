class Solution {
public:
  int sqrt(int x) {
    if (x == 0) {
      return 0;
    }
    int lo = 1, hi = x;
    while (lo <= hi) {
      int mi = (lo + hi) / 2;
      if (mi <= x/mi) {
	lo = mi + 1;
      } else {
	hi = mi-1;
      }
    }
    return hi;
  }
};
