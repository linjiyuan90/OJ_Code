#include "numeric"
#include "iostream"
#include "string"
#include "algorithm"
#include "vector"

int min_actions(std::vector<int>& lens) {
  std::sort(lens.begin(), lens.end());
  int m1 = lens.size()/2, m2 = lens.size() - 1 - m1;
  m1 = lens[m1];
  m2 = lens[m2];
  int ans1 = std::accumulate(lens.begin(), lens.end(), 0,
                             [&m1](int sum, int x) {
                               return sum + ::abs(x-m1);
                             });
  int ans2 = ans1;
  if (m2 != m1) {
    ans2 = std::accumulate(lens.begin(), lens.end(), 0,
                          [&m2](int sum, int x) {
                            return sum + ::abs(x-m2);
                          });
  }
  return std::min(ans1, ans2);
}

int min_actions(const std::vector<std::string>& strs) {
  std::vector<std::pair<char, std::vector<int>>> charLens;
  bool first = true;
  for (const auto& str : strs) {
    int k = 0;
    for (std::size_t i = 0, n = str.length(); i < n; ++k) {
      std::size_t j = str.find_first_not_of(str[i], i+1);
      if (j == std::string::npos) {
        j = str.length();
      }
      if (first) {
        charLens.push_back({str[i], std::vector<int>{j - i}});
      } else if (k < charLens.size() && charLens[k].first == str[i]) {
        charLens[k].second.push_back(j - i);
      } else {
        return -1;
      }
      i = j;
    }
    if (k != charLens.size()) {
      return -1;
    }
    first = false;
  }
  int min = 0;
  for (auto& pair : charLens) {
    min += min_actions(pair.second);
  }
  return min;
}

int main() {
  int T, t = 1, n;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n;
    std::vector<std::string> strs(n);
    for (auto& str: strs) {
      std::cin >> str;
    }
    int ans = min_actions(strs);
    if (ans == -1) {
      std::cout << "Fegla Won" << std::endl;
    } else {
      std::cout << ans << std::endl;
    }
  }
  return 0;
}
