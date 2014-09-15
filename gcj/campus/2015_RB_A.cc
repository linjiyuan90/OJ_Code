#include "iostream"
#include "vector"

using namespace std;

namespace Stirling {

const long long Mod = 1000000007;
const int Max = 100;

std::vector<std::vector<long long>> stirling(Max + 1);
std::vector<long long> factorial(Max+1);

void init() {
  stirling[0].push_back(1);
  factorial[0] = 1;
  for (int n = 1; n <= Max; ++n) {
    stirling[n].resize(n+1);
    stirling[n][n] = 1;
    for (int m = 1; m < n; ++m) {
      stirling[n][m] = (stirling[n-1][m-1] + stirling[n-1][m] * m) % Mod;
    }
    factorial[n] = factorial[n-1] * n % Mod;
  }
}

long long ways(int n, int m) {
  return stirling[n][m] * factorial[m] % Mod;
}

// another solutions is 
// dp[n][m] = dp[n-1][m-1] * m + dp[n-1][m] * m
long long waysByDp(int n, int m) {
  std::vector<std::vector<long long>> dp(n+1, std::vector<long long>(m+1));
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      dp[i][j] = (dp[i-1][j-1] * j + dp[i-1][j] * j) % Mod;
    }
  }
  return dp[n][m];
}

}

int main() {
  Stirling::init();
  int T, n, m, t = 1;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> m >> n;
    // the answer is Stiring(n, m) * m!
    // std::cout << Stirling::ways(n, m) << std::endl;
    std::cout << Stirling::waysByDp(n, m) << std::endl;
  }
  return 0;
}
