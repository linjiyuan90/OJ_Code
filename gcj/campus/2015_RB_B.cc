#include "iostream"
#include "tuple"
#include "unordered_map"
#include "iomanip"

using namespace std;

// one glass can take only one third of its parents (at most 3 parents)
// dp[l][n][m] <- dp[l-1][n][m]/3 + dp[l-1][n-1][m-1]/3 + dp[l-1][n-1][m]/3
// 1 <= m <= n <= l
// id(n, m) = n*(n-1)/2 + m

namespace Party {

const int MaxL = 400;

std::unordered_map<int, std::unordered_map<int, double>> glass;

std::tuple<int, int> unpack(int N) {
  int n, sum;
  for (sum = 0, n = 1; sum + n < N; sum += n, ++n);
  return {n, N - sum};
}

int pack(int n, int m) {
  return n*(n-1)/2 + m - 1;
}

double howMuch(int l, int n, int m) {
  if (glass[l].count(pack(n, m))) {
    return glass[l][pack(n, m)];
  }
  double& ans = glass[l][pack(n, m)];
  if (n < l) {
    ans += std::max(0.0, howMuch(l-1, n, m) - 1) / 3;
  }
  if (m > 1) {
    ans += std::max(0.0, howMuch(l-1, n-1, m-1) - 1) / 3;
  }
  if (n > m) {
    ans += std::max(0.0, howMuch(l-1, n-1, m) - 1) / 3;    
  }
  return ans;
}

double howMuch(int l, int n, int m, int cups) {
  glass.clear();
  glass[1][0] = cups;
  return howMuch(l, n, m);
}

}

int main() {
  int T, t = 1, B, L, N;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cout << std::fixed << std::setprecision(7);
    std::cin >> B >> L >> N;
    int n, m;
    std::tie(n, m) = Party::unpack(N);
    std::cout << std::min(1.0, Party::howMuch(L, n, m, B * 3)) * 250 << std::endl;
  }
  return 0;
}
