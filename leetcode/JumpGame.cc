class Solution {
public:
  // no need to dp
  bool canJump(int A[], int n) {
    for (int s = 0, e = 0; ;) {
      if (e >= n - 1) {
	return true;
      }
      int ss = e, ee = e;
      for (int i = s; i <= e; ++i) {
	ee = std::max(ee, i + A[i]);
      }
      // no advance
      if (e == ee) {
	break;
      }
      s = ss;
      e = ee;
    }
    return false;
  }
};
