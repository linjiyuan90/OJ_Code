// differet version of binary search
{
  int lo = 0, hi = n;
  while (lo < hi) {
    int mi = (lo + hi) / 2;
    if (A[mi] < target) {
      lo = mi + 1;
    } else {
      hi = mi;
    }
  }
  return lo < n && A[lo] == target;
}
