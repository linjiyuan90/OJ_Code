/*
  Given a sequence, each element can +/- a different value [0, m].
  1) Find a minimum m, which make the new sequence increasing strictly
  2) With this m, calculate the min(sum(value_i))
  
  For example: 2, 2, 2 => 1 2 3

  1) A binary search can solve it.
     But there is a O(n) solution!!!

  2) Bruce DP is out-of-space. The solution is to use SkewHeap, HARD!!!!
     Sth like http://blog.watashi.ws/2067/zojmonthly1106/
     ZOJ3512. Financial Fraud
*/

#include "iostream"
#include "vector"
#include "map"

bool is_valid(int m, const std::vector<int>& seq) {
  int low = INT_MIN, high = INT_MAX;
  for (auto& x : seq) {
    low = std::max(low + 1, x - m);
    high = x + m;
    if (low > high) {
      return false;
    }
  }
  return true;
}

std::pair<int, int> solve(const std::vector<int>& seq) {
  if (seq.empty()) {
    return {0, 0};
  }
  // first, use binary search to find the minimum m
  int low = 0, high = 1000000;
  while (low < high) {
    int mid = (low + high) / 2;
    if (is_valid(mid, seq)) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  int m = low;

  // then do a dp?
  std::map<int, int> pre, now;
  for (int x = seq[0], y = x - m; y <= x + m; ++y) {
    pre[y] = abs(x - y);
  }
  for (int i = 1, n = seq.size(); i < n; ++i) {
    int p = INT_MAX;
    for (auto& it : pre) {
      it.second = std::min(it.second, p);
      p = it.second;
    }
    for (int x = seq[i], y = x - m; y <= x + m; ++y) {
      auto it = pre.find(y - 1);
      if (it != pre.end()) {
	now[y] = abs(x - y) + it->second;
      }
    }
    pre = now;
    now.clear();
  }
  int ans = INT_MAX;
  for (auto& it : pre) {
    ans = std::min(ans, it.second);
  }
  return {m, ans};
}

template<typename A, typename B>
std::ostream& operator << (std::ostream& os, std::pair<A, B> p) {
  return os << p.first << " " << p.second;
}

int main() {
  for (int n; std::cin >> n; ) {
    std::vector<int> seq(n);
    for (auto& x : seq) {
      std::cin >> x;
    }
    std::cout << solve(seq) << std::endl;
  }
}
