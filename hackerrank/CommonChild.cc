#include "string"
#include "iostream"
#include "vector"

int longest_common_sequence(const std::string& A, const std::string& B) {
  int n = A.size(), m = B.size();
  std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      dp[i+1][j+1] = dp[i][j] + (A[i] == B[j]);
      dp[i+1][j+1] = std::max(dp[i+1][j+1], dp[i+1][j]);
      dp[i+1][j+1] = std::max(dp[i+1][j+1], dp[i][j+1]);
    }
  }
  return dp[n][m];
}

int main() {
  for (std::string A, B; std::cin >> A >> B; ) {
    std::cout << longest_common_sequence(A, B) << std::endl;
  }
}
