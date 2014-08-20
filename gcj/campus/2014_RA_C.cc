#include "iostream"
#include "vector"
#include "algorithm"

inline bool is_odd(const int x) {
  return x % 2;
}

int main() {
  int T, t = 1, n;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n;
    std::vector<int> books(n);
    std::vector<int> alice, bob;
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> books[i];
      if (is_odd(books[i])) {
        alice.push_back(i);
      } else {
        bob.push_back(i);
      }
    }
    auto sep = std::partition(books.begin(),
                              books.end(),
                              is_odd);
    std::sort(books.begin(), sep);
    std::sort(sep, books.end(), std::greater<int>());
    std::vector<int> res(n);
    for (std::size_t i = 0; i < alice.size(); ++i) {
      res[alice[i]] = books[i];
    }
    for (std::size_t i = 0, m = sep - books.begin(); i < bob.size(); ++i) {
      res[bob[i]] = books[m+i];
    }
    for (std::size_t i = 0; i < n; ++i) {
      if (i > 0) {
        std::cout << " ";
      }
      std::cout << res[i];
    }
    std::cout << std::endl;
  }
  return 0;
}
