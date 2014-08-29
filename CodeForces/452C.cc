/*
  m identitcal decks of cards, each with number n. Sample n from these decks to form a new deck.
  What's the probablity of getting two identical cards in two pulls with placement.

  let p(k) be the probability that the card 1 appears in the new deck k times
  p(k) = C(m, k)*C((n-1)*m, n-k)/C(n*m, n), 0 <= k <= m

  So, the final prob is: n * sum{p(k)*(k/n)^2}
*/
#include "iostream"
#include "cmath"
#include "vector"

double trickProbability(int n, int m) {
  std::vector<double> p(std::min(n, m)+1, 1.0);
  for (int k = 0; k <= std::min(m, n); ++k) {
    for (int i = 0; i < n; ++i) {
      if (i < k) {
        p[k] *= 1.0*(m-i)/(i+1);
      } else {
        p[k] *= 1.0*((n-1)*m-i+k)/(i-k+1);
      }
      p[k] /= 1.0*(n*m-i)/(i+1);
    }
  }
  double ans = 0.0;
  for (int k = 1; k <= std::min(n, m); ++k) {
    ans += p[k] * k/n *k/n;
  }
  return n*ans;
}

int main() {
  for (int m, n; std::cin >> n >> m; ) {
    std::cout << trickProbability(n, m) << std::endl;
  }
  return 0;
}
