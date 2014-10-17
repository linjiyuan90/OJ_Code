#include "iostream"
#include "vector"
#include "string"
#include "unordered_map"
#include "algorithm"
#include "set"
#include "functional"

namespace Click {

std::unordered_map<int, int> dp;

void clear() {
  dp.clear();
}

int solve(const std::vector<int>& click, int x) {
  if (dp.count(x)) {
    return dp[x];
  }
  std::string xStr = std::to_string(x);
  dp[x] = std::all_of(xStr.begin(), xStr.end(), [&click](const char& ch) {
      return click[ch - '0'];
    }) ? xStr.length() : -1;
  for (int y = 2; y <= x / y; ++y) {
    if (x % y != 0) {
      continue;
    }
    std::string yStr = std::to_string(y);
    if (!std::all_of(yStr.begin(), yStr.end(), [&click](const char& ch) {
        return click[ch - '0'];
        })) {
      continue;
    }
    int left = solve(click, y);
    if (left == -1) {
      continue;
    }
    int right = solve(click, x/y);
    if (right == -1) {
      continue;
    }
    if (dp[x] == -1 || dp[x] > left + right + 1) {
      dp[x] = left + right + 1;
    }
  }
  return dp[x];
}

}

int main() {
  int T, t = 1, x;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::vector<int> click(10);
    for (auto& c : click) {
      std::cin >> c;
    }
    std::cin >> x;
    Click::clear();
    int c = Click::solve(click, x);
    if (c == -1) {
      std::cout << "Impossible" << std::endl;
    } else {
      std::cout << c + 1 << std::endl;
    }
  }
  return 0;
}
