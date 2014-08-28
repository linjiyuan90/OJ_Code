#include "algorithm"

// k starts from 1 will be easier
template<typename Iter>
Iter findK(Iter aBeg, Iter aEnd, Iter bBeg, Iter bEnd, int k) {
  if (aBeg == aEnd) {
    return bBeg + k - 1;
  }
  if (bBeg == bEnd) {
    return aBeg + k - 1;
  }
  // check empty array first
  if (k == 1) {
    return *aBeg < *bBeg ? aBeg : bBeg;
  }
  int aN = aEnd - aBeg;
  int bN = bEnd - bBeg;
  if (k == aN + bN) {
    return *(aEnd-1) < *(bEnd-1) ? bEnd-1 : aEnd-1;
  }
  int ak = std::min(aN, k / 2);
  int bk = k - ak;
  if (bk >= bN) {
    bk = bN;
    ak = k - bk;
  }
  Iter aMid = aBeg + ak - 1;
  Iter bMid = bBeg + bk - 1;
  return *aMid < *bMid ? 
                 findK(aMid+1, aEnd, bBeg, bEnd, k - ak) : 
    findK(aBeg, aEnd, bMid+1, bEnd, k - bk);
}

int solution(vector<int> &A, vector<int> &B, vector<int> &P, vector<int> &Q, vector<int> &R, vector<int> &S) {
  std::vector<int> res;
  for (std::size_t i = 0, k = P.size(); i < k; ++i) {
    res.push_back(*findK(A.begin() + P[i], 
                         A.begin() + Q[i] + 1,
                         B.begin() + R[i],
                         B.begin() + S[i] + 1,
                         (Q[i]-P[i]+1+S[i]-R[i]+1+1)/2));    
  }
  std::sort(res.begin(),res.end());
  return res[res.size()/2];
}
