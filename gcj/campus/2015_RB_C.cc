#include "iostream"
#include "tuple"
#include "unordered_map"
#include "iomanip"
#include "vector"

using namespace std;

namespace PlayBoy {

const int Max = 100;

std::vector<std::vector<int>> dp(Max + 1, std::vector<int>(Max+1));

int discard(const std::vector<int>& seq, int x, int y, int k) {
  if (dp[x][y] != -1) {
    return dp[x][y];
  }
  int& ans = dp[x][y];
  ans = y - x + 1;
  int a = x, b, c;
  // trying to find a three adjacent value for a
  for (b = a + 1; b < y; ++b) {
    if (seq[b] - seq[a] == k && discard(seq, a+1, b-1, k) == 0) {
      for (c = b + 1; c <= y; ++c) {
        if (seq[c] - seq[b] == k && discard(seq, b+1, c-1, k) == 0) {
          ans = std::min(ans, discard(seq, c+1, y, k));
        }
      }
    }
  }
  // if not found, forget a
  ans = std::min(ans, 1 + discard(seq, a+1, y, k));
  return ans;
}

int discard(const std::vector<int>& seq, int k) {
  int n = seq.size();
    for (int i = 0; i < n; ++i) {
      std::fill(dp[i].begin(), dp[i].begin() + n, -1);
  }
  return discard(seq, 0, n-1, k);
}

}

int main() {
  int T, t = 1, n, k;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n >> k;
    std::vector<int> seq(n);
    for (auto& s : seq) {
      std::cin >> s;
    }
    std::cout << PlayBoy::discard(seq, k) << std::endl;
  }
  return 0;
}
