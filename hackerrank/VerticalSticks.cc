/*
 Given an array Y = [y1, .. yn], define vi = min(i-j), j < i, yj >= yi.
 And V = ∑vi
 Let's permuate Y, what's expectation of V
 
 E[V] = E[∑vi] = ∑E[vi]
 Consider every yi in every possible position, and calculate its vi.
 E[vi] = 1/n∑E[vi when yi at pos[k]] = 1/n∑∑(k-j)p(yi,k,j)
 p(yi, k, j) means the probability of yi at position k, and the first y >= yi
 is at j.
 p(yi, k, j) = (numGe(Y, yi) - 1) / (n-(k-j)) * C(numLt(Y, yi), k-j-1) / C(n-1, k-j-1)
 numGe(Y, yi) means how many numbers in Y that >= yi
 numLt(Y, yi) means how many numbers in Y that < yi
 */
#include "iostream"
#include "vector"
#include "algorithm"
#include "iomanip"

double C(int n, int k) {
  double ans = 1.0;
  for (int i = 0; i < k; ++i) {
    ans *= 1.0 * (n-i) / (i+1);
  }
  return ans;
}

int main() {
  int T, n;
  for (std::cin >> T; T--; ) {
    std::cin >> n;
    std::vector<int> Y(n);
    for (auto& y : Y) {
      std::cin >> y;
    }
    std::sort(Y.begin(), Y.end());
    double E = 0.0;
    for (auto& y : Y) {
      auto it = std::lower_bound(Y.begin(), Y.end(), y);
      int numGe = static_cast<int>(Y.end() - it);
      int numLt = static_cast<int>(it - Y.begin());
      double e = 0.0;
      for (int k = 1; k <= n; ++k) {
        double ek = 0.0;
        for (int j = k - 1; j > 0; --j) {
          if (numLt < k-j-1) {
            break;
          }
          ek += C(numLt, k-j-1) / C(n-1, k-j-1) * (numGe - 1)/(n-(k-j)) * (k-j);
        }
        int j = 0;
        if (numLt >= k-j-1) {
          ek += C(numLt, k-j-1) / C(n-1, k-j-1) * (k-j);
        }
        e += ek;
      }
      E += e / n;
    }
    std::cout << std::fixed << std::setprecision(2) << E << std::endl;
  }
  return 0;
}
