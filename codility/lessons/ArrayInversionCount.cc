#include "algorithm"

typedef std::vector<int>::iterator Iter;

int inversions(Iter beg, Iter end) {
  int n = end - beg;
  if (n <= 1) {
    return 0;
  }
  Iter mid = beg + n / 2;
  int ans = inversions(beg, mid) + inversions(mid, end);
  std::vector<int> tmp(n);
  Iter left = beg, right = mid, res = tmp.begin();
  while (left < mid || right < end) {
    if (right == end || left < mid && *left <= *right) {
      *res ++ = *left ++;
    } else {
      ans += mid - left;
      *res ++ = *right ++;
    }
  }
  std::copy(tmp.begin(), tmp.end(), beg);
  return ans;
}

int solution(const vector<int> &A) {
  auto arr = A;
  return inversions(arr.begin(), arr.end());
}
