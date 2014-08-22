/*
  Given (A, B, K), how many pairs (a, b) that: a & b < K, a < A, b < B
  
  Official solutions:
  1. divide the search space into different sets, computes the size of each set recursively
  Let S(A, B, K) denote such pairs (a, b), discuss (a, b)'s lowest bits
  1) a is even, b is even, then add S(ceil(A/2), ceil(B/2), ceil(K/2)); note here use ceil!
  2) a is even, b is odd, then add S(ceil(A/2), floor(B/2), ceil(K/2)); K still use ceil, since low(a&b) = 0
  3) a is odd, b is even, then add S(floor(A/2), ceil(B/2), ceil(K/2)); K still use ceil, since low(a&b) = 0
  4) a is odd, b is odd, then add S(floor(A/2), floor(B/2), floor(K/2));
  
  2. bit/digit counting
  Cool! A general framework of counting numbers that < K, is
  count(i, lessK, K):
    if i == -1: reutrn lessK
    maxK = lessK or ((K>>i)&1)
    // set i bit as 0
    ans = count(i-1, maxK, K)
    if maxK:
      // set i bit as 1
      ans += count(i-1, lessK, K)
    return ans

  With respect to this problem, that is to count(i, lessA, lessB, lessK, A, B, K)
  Enumerate possible value of current bit of a, b
*/

#include "unordered_map"
#include "iostream"
#include "algorithm"
#include "functional"
#include "vector"
#include "tuple"

template<typename A, typename B, typename C>
class TripletHash {
  std::hash<A> aHash;
  std::hash<B> bHash;
  std::hash<C> cHash;
public:
  std::size_t operator() (const std::tuple<A, B, C>& tuple) const {
    return 
      aHash(std::get<0>(tuple)) ^ 
      bHash(std::get<1>(tuple)) ^ 
      cHash(std::get<2>(tuple));
  }
};

// namespace or class?
// class seems better, since it can hide the variable
class NewLotteryGame {
  static std::unordered_map<std::tuple<int, int, int>, 
                            long long,
                            TripletHash<int, int, int>> memo;
  static std::unordered_map<std::tuple<int, int, int>, 
                            long long,
                            TripletHash<int, int, int>> memoBit[31];
 
  static long long calcPairsByDP(int i,
                                 bool lessA, bool lessB, bool lessK,
                                 int A, int B, int K) {
    if (i == -1) {
      return lessA && lessB && lessK;
    }
    if (memoBit[i].count({lessA, lessB, lessK})) {
      return memoBit[i][{lessA, lessB, lessK}];
    }
    long long& ans = memoBit[i][{lessA, lessB, lessK}];
    bool maxA = lessA || ((A>>i)&1); 
    bool maxB = lessB || ((B>>i)&1); 
    bool maxK = lessK || ((K>>i)&1); 
    // ai = 0, bi = 0
    ans += calcPairsByDP(i-1, maxA, maxB, maxK, A, B, K);
    // ai = 1, bi = 0
    if (maxA) {
      ans += calcPairsByDP(i-1, lessA, maxB, maxK, A, B, K);
    }
    // ai = 0, bi = 1
    if (maxB) {
      ans += calcPairsByDP(i-1, maxA, lessB, maxK, A, B, K);
    }
    // ai = 1, bi = 1
    if (maxA && maxB && maxK) {
      ans += calcPairsByDP(i-1, lessA, lessB, lessK, A, B, K);
    }
    return ans;
  }

public:
  static long long calcPairsByRecursion(int A, int B, int K) {
    if (A == 0 || B == 0 || K == 0) {
      return 0;
    }
    if (A == 1 && B == 1) {
      return K > 0;
    }
    if (memo.count({A, B, K})) {
      return memo[{A, B, K}];
    }
    return memo[{A, B, K}] =
      // a is even, b is even
      calcPairsByRecursion((A+1)>>1, (B+1)>>1, (K+1)>>1) +
      // a is even, b is odd
      calcPairsByRecursion((A+1)>>1, B>>1, (K+1)>>1) +
      // a is odd, b is even
      calcPairsByRecursion(A>>1, (B+1)>>1, (K+1)>>1) +
      // a is odd, b is odd
      calcPairsByRecursion(A>>1, B>>1, K>>1);
  }
  
  static long long calcPairsByDP(int A, int B, int K) {
    // clear memo first, since it's specifiec to (A, B, K)
    for (int i = 0; i < 31; ++i) {
      memoBit[i].clear();
    }
    return calcPairsByDP(30, false, false, false, A, B, K);
  }
};

std::unordered_map<std::tuple<int, int, int>, 
                   long long,
                   TripletHash<int, int, int>> NewLotteryGame::memo;
std::unordered_map<std::tuple<int, int, int>, 
                   long long,
                   TripletHash<int, int, int>> NewLotteryGame::memoBit[31];


int main() {
  int T, t = 1, n;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    int A, B, K;
    std::cin >> A >> B >> K;
    std::cout << NewLotteryGame::calcPairsByDP(A, B, K) << std::endl;
    // std::cout << NewLotteryGame::calcPairsByRecursion(A, B, K) << std::endl;
  }
  return 0;
}


