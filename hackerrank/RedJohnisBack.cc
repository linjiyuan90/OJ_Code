/*
  let ways of puting 1*4, 4*1 bricks to 4*n walls be m.
  How many primes in [1, m]
  n <= 40
  
  ways[n] = ways[n-1] + ways[n-4];
*/

#include "iostream"
#include "algorithm"
#include "vector"

namespace RedJohn {

const int MaxN = 40;

std::vector<int> primes;
std::vector<int> ways;

void init() {
  ways.resize(MaxN + 1);
  ways[0] = 1;
  for (int n = 1; n <= MaxN; ++n) {
    ways[n] = ways[n-1] + (n >= 4 ? ways[n-4] : 0);
  }
  // ways[MaxN] 217286
  
  for (int p = 2; p <= ways[MaxN]; ++p) {
    bool isPrime = true;
    for (auto& pi : primes) {
      if (p % pi == 0) {
        isPrime = false;
        break;
      }
    }
    if (isPrime) {
      primes.push_back(p);
    }
  }
}

int numPrimes(int n) {
  return
    std::upper_bound(primes.begin(), primes.end(), ways[n]) - primes.begin();
}

}

int main() {
  RedJohn::init();
  int T, n;
  for (std::cin >> T; T--; ) {
    std::cin >> n;
    std::cout << RedJohn::numPrimes(n) << std::endl;
  }
  return 0;
}
