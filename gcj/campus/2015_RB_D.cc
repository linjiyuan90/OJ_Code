#include "iostream"
#include "string"
#include "vector"
#include "list"
#include "map"
#include "cassert"

using namespace std;

namespace Parentheses {

const int Max = 100;
const long long MaxF = 1000000000000000001LL;

// f[n, k] n pairs with k parts:
// ((..))|((..))|...
std::vector<std::vector<long long>> f(Max + 1, std::vector<long long>(Max + 1));
std::vector<long long> sumF(Max + 1);

void init() {
  f[0][0] = 1;
  sumF[0] = 1;
  for (int n = 1; n <= Max; ++n) {
    for (int k = 1; k <= n; ++k) {
      for (int l = 0; l < n; ++l) {
        if (1.0 * sumF[l] * f[n-l-1][k-1] >= MaxF) {
          f[n][k] = MaxF;
          break;
        }
        f[n][k] += sumF[l] * f[n-l-1][k-1];
      }
      sumF[n] += f[n][k];
      sumF[n] = std::min(sumF[n], MaxF);
    }
  }
}

long long gcd(long long a, long long b) {
  return b == 0 ? a : gcd(b, a % b);
}

long long comb(int n, int k) {
  k = std::min(k, n - k);
  // check if larger than MaxF
  double d = 1.0;
  for (int i = 0; i < k; ++i) {
    d *= (n-i);
    d /= (i+1);
  }
  if (d >= MaxF) {
    return MaxF;
  }
  // 
  long long a = 1, b = 1;
  for (int i = 0; i < k; ++i) {
    a *= (n-k+1+i);
    b *= (k-i);
    long long g = gcd(a, b);
    a /= g;
    b /= g;
  }
  return a / b;
}

// k start from zero
std::string construct(int n, long long k) {
  std::string res;
  for (int i = 0, left = 0; i < 2*n; ++i) {
    if (left > 0) {
      // two choice, '(', or ')'
      // choose '(' if k < all possible combinations in [i+1, 2n)
      
      // now have left nunmber of '(', (i-left)/2 pairs in the front
      // so there are p = n-(i-left)/2-1 pairs can be arranged.
      // the ways are: sum(f[p][m]*C(m+left+1, m))
      long long ways = 0;
      int p = n - (i-left)/2 - (left+1);
      for (int m = 0; m <= p; ++m) {
        long long c = comb(m+left+1, m);
        if (MaxF / c <= f[p][m]) {
          ways = MaxF;
          break;
        }
        ways += f[p][m] * c;
        if (ways >= MaxF) {
          break;
        }
      }
      if (ways > k) {
        ++ left;
        res.push_back('(');
      } else {
        -- left;
        k -= ways;
        res.push_back(')');
      }
    } else {
      ++left;
      res.push_back('(');
    }
  }
  return res;
}
}

int main() {
  Parentheses::init();
  int T, n, t = 1;
  long long k;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n >> k;
    if (k > Parentheses::sumF[n]) {
      std::cout << "Doesn't Exist!" << std::endl;
    } else {
      std::cout << Parentheses::construct(n, k-1) << std::endl;
    }
  }
  return 0;
}
