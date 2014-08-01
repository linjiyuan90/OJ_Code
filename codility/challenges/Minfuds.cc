/*
  Given a set of linear function F(x, K) = A[K]*X + B[K], find the minimum gap S(x), where 
  S(x) = max{F(x, K)} - min{F(x, K)}

  Since max - min is a convex function, this problem can be solved using trinary search.
  However, this is NOT O(NlogN)!!!

  The O(NlogN) solution should be able to find all the intersection in O(NlogN).
  
*/





////////////////////////////////////////////////////////////////////////////////
// Trinary Search
////////////////////////////////////////////////////////////////////////////////

// NOTE!!!
// if x >> Bi, then Ai*x + Bi will erase B!
// So if Ai == Aj, then Ai*x + Bi == Aj*x + Bj, which is wrong!
// So x should not be too large to lost precision.

double diff(const std::vector<int>& A, const std::vector<int>& B, const double x) {
  double min = A[0]*x + B[0], max = min;
  for (int i = 0, n = A.size(); i < n; ++i) {
    double y = A[i]*x + B[i];
    min = std::min(min, y);
    max = std::max(max, y);
  }
  return max - min;
}

// binary search won't work for trinary problem!
// But the vice is ok.
double solution(const std::vector<int> &A, const std::vector<int> &B) {
  double low = -1e10, high = 1e10;
  for (int cnt = 0; cnt < 200 && low < high; ++cnt) {
    double one3rd = (high - low) / 3.0;
    double mid1 = low + one3rd, mid2 = high - one3rd;
    if (diff(A, B, mid1) > diff(A, B, mid2)) {
      low = mid1;
    } else {
      high = mid2;
    }
  }
  return diff(A, B, (low + high) / 2);
}
