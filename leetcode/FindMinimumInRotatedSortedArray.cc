class Solution {
public:
  int findMin(vector<int> &num) {
    int lo = 0, hi = num.size() - 1;
    // restrict to rotated sorted array
    while (lo < hi && num[lo] > num[hi]) {
      int mi = (lo + hi) / 2;
      if (num[lo] <= num[mi]) {
        lo = mi + 1;
      } else {
        hi = mi;
      }
    }
    return num[lo];
  }
};
