/*
  Calculate sum of max{a[i..j]} - min{a[i..j]} for all interval i..j
*/

#include "iostream"
#include "vector"
#include "deque"

long long max_min_sum(const std::vector<int>& vt) {
  long long res = 0;
  // (height, length)
  std::deque<std::pair<int, int> > desc, asc;
  long long max_sum = 0, min_sum = 0;
  for (int i = 0, n = vt.size(); i < n; ++i) {
    int len = 1;
    while(!desc.empty() && desc.back().first <= vt[i]) {
      len += desc.back().second;
      max_sum -= 1ll * desc.back().first * desc.back().second;
      desc.pop_back();
    }
    desc.push_back(std::make_pair(vt[i], len));
    max_sum += 1ll * vt[i] * len;
    len = 1;
    while(!asc.empty() && asc.back().first >= vt[i]) {
      len += asc.back().second;
      min_sum -= 1ll * asc.back().first * asc.back().second;
      asc.pop_back();
    }
    asc.push_back(std::make_pair(vt[i], len));
    min_sum += 1ll * vt[i] * len;
    res += max_sum - min_sum;
  }
  return res;
}

int main() {
  for (int n; std::cin >> n;) {
    std::vector<int> vt(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> vt[i];
    }
    std::cout << max_min_sum(vt) << std::endl;
  }
  return 0;
}
