#include "iostream"
#include "vector"
#include "numeric"

int main() {
  for (int n; std::cin >> n; ) {
    std::vector<int> ratings(n);
    std::vector<int> candies(n, 1);
    for (auto& r : ratings) {
      std::cin >> r;
    }
    for (int i = 1; i < n; ++i) {
      if (ratings[i-1] < ratings[i]) {
        candies[i] = std::max(candies[i], candies[i-1] + 1);
      }
    }
    for (int i = n-2; i >= 0; --i) {
      if (ratings[i+1] < ratings[i]) {
        candies[i] = std::max(candies[i], candies[i+1] + 1);
      }
    }
    std::cout << std::accumulate(candies.begin(), candies.end(), 0) << std::endl;
  }
  return 0;
}
