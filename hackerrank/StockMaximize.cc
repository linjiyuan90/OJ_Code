/*
  Each day, you can either buy one share of WOT, sell any number of shares of WOT that you own,
  or not make any transaction at all. 

  From right to left,
  if current price >= maxRight, update maxRight
  else sum += maxRight - cur

  Extension:
  what about can only sell after m days / within m days?
  1) after m days is easy, like above algorithm
  2) within m days, I don't have any clue currently
*/
#include "vector"
#include "iostream"
#include "algorithm"

int main() {
  int T, n;
  for (std::cin >> T; T--;) {
    std::cin >> n;
    std::vector<int> stocks(n);
    for (auto& p : stocks) {
      std::cin >> p;
    }
    long long sum = 0;
    int maxRight = 0;
    for (int i = n - 1; i >= 0; --i) {
      if (stocks[i] >= maxRight) {
        maxRight = stocks[i];
      } else {
        sum += maxRight - stocks[i];
      }
    }
    std::cout << sum << std::endl;
  }
  return 0;
}
