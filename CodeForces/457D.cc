/*
  n*n grid are generated from distinct in [1, m].
  Now, select k distinct numbers from [1, m], and mark the corresponding grids.
  Calculuate:
  E = ∑2^(r+c) * P(r, c)
  Here, P(r, c) means the probability that r rows, c columns in grid 
  that are fully marked, no more other rows/columns are fully marked.

  http://codeforces.com/blog/entry/13855

  The score 2^(r+c) is the number of all the subsets of (r+c), so change the formula:
  E = ∑|subset of (r, c)| * P(r, c)
    = ∑ (r, c) * ∑ P(superset of (r, c))
    = ∑ (r, c) * P'(r, c)
  Here, (r, c) means the specific r rows, c columns are fully marked, while other fully
  marked rows/columns is still possible. P'(r, c) is the probability of the k distinct
  numbers can mark the specific rows, columns.
  
  So, enumerate all possible (r, c), that's C(n, r) * C(n, c).
  let N(r, c) be the number of grid of the specific rows/columns, then
  N(r, c) = (r+c)*n - r*c
  P'(r, c) = C(k-N(r,c), k) / C(m-N(r,c), m)
*/
#include "iostream"
#include "algorithm"
#include "vector"
#include "cmath"
#include "iomanip"

double log10Comb(int n, int k) {
  double ans = 0.0;
  for (int i = 0; i < k; ++i) {
    ans += ::log10(n-i) - ::log10(i+1);
  }
  return ans;
}

int main() {
  for (int n, m, k; std::cin >> n >> m >> k;) {
    // init first
    std::vector<double> log10CombN(n+1);
    std::vector<double> log10CombK(n*n+1);
    std::vector<double> log10CombM(n*n+1);
    for (int i = 1; i <= n; ++i) {
      log10CombN[i] = log10CombN[i-1] + ::log10(n-i+1) - ::log10(i);
    }
    for (int i = 1; i <= n*n; ++i) {
      log10CombK[i] = log10CombK[i-1] + ::log10(k-i+1) - ::log10(i);
      log10CombM[i] = log10CombM[i-1] + ::log10(m-i+1) - ::log10(i);
    }
    double E = 0;
    for (int r = 0; r <= n; ++r) {
      for (int c = 0; c <= n; ++c) {
        int nrc = (r+c)*n - r*c;
        if (nrc > k) {
          continue;
        }
        /*
        double log10RC = 
          log10Comb(n, r) + log10Comb(n, c) + 
          log10Comb(k, nrc) - log10Comb(m, nrc);
        */
        double log10RC = 
          log10CombN[r] + log10CombN[c] +
          log10CombK[nrc] - log10CombM[nrc];
        E += ::pow(10, log10RC);
        if (E > 1e99) {
          break;
        }
      }
      if (E > 1e99) {
        break;
      }
    }
    std::cout << std::fixed << std::setprecision(9) << std::min(E, 1e99) << std::endl;
  }
  return 0;
}
