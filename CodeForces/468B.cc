#include "numeric"
#include "iostream"
#include "map"
#include "vector"
#include "algorithm"

// 1 2 3 4
// a = 3, b = 5
// A: (1, 2)
// B: (1, 4), (2, 3)

// One number can have at most 2 match: a-x, b-x
// Suppose we start from the minimal number x
// if b-x exists, then b-x must match x;
// otherwise, any elements y > x will make b-x + y > b, illegal
// if a-x and b-x both exists, match b-x first, as analysized above. And possibly a-x can have b-(a-x) option
// if only a-x exists, x match a-x

int main() {
  for (int n, a, b; std::cin >> n >> a >> b; ) {
    int A = 0, B = 1;
    if (a > b) {
      std::swap(a, b);
      std::swap(A, B);
    }
    std::vector<int> ans(n, -1);
    std::map<int, int> pos;
    for (int i = 0, x; i < n; ++i) {
      std::cin >> x;
      pos[x] = i;
    }
    while(!pos.empty()) {
      int x = pos.begin()->first;
      // try b first!
      if (pos.count(b - x)) {
        ans[pos[x]] = ans[pos[b-x]] = B;
        pos.erase(x);
        pos.erase(b-x);
        continue;
      }
      if (pos.count(a - x)) {
        ans[pos[x]] = ans[pos[a-x]] = A;
        pos.erase(x);
        pos.erase(a-x);
        continue;
      }
      break;
    }
    
    if (std::count(ans.begin(), ans.end(), -1) == 0) {
      std::cout << "YES" << std::endl;
      for (int i = 0; i < n; ++i) {
        if (i > 0) {
          std::cout << " ";
        }
        std::cout << ans[i];
      }
      std::cout << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
  return 0;
}
