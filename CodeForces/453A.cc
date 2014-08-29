/*
  The expectation of m dices n runs max value.
  p(k) = (k/m)^n - (k-1/m)^n
*/
#include "iostream"
#include "cmath"

double maxDiceExpectation(int m, int n) {
  double ans = 0.0;
  for (int k = 1; k <= m; ++k) {
    ans += k * (pow(1.0*k/m, n) - pow(1.0*(k-1)/m, n));
  }
  return ans;
}

int main() {
  for (int m, n; std::cin >> m >> n; ) {
    std::cout << maxDiceExpectation(m, n) << std::endl;
  }
  return 0;
}
