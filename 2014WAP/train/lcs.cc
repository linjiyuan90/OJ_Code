#include "iostream"
#include "string"
#include "vector"

std::string lcs(const std::string &a, const std::string &b) {
  int n = a.size(), m = b.size();
  std::string ans;
  std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      dp[i+1][j+1] = a[i] == b[j] ? dp[i][j] + 1 : 0;
      if (dp[i+1][j+1] > ans.size()) {
	ans = a.substr(i - dp[i+1][j+1] + 1, dp[i+1][j+1]);
      }
    }
  }
  return ans;
}

int main() {
  for (std::string a, b; std::cin >> a >> b;) {
    std::cout << lcs(a, b) << std::endl;
  }
}
