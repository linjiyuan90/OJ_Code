#include "iostream"
#include "deque"
#include "map"
#include "vector"

class Solution {
public:
  // for problem a + b = target
  // this can be done in O(n) by using two pointers, no need to find 
  // b = target - a
  // (assume the elements are sorted)
  // So, 4sum can be solved in O(n^3)
  std::vector<std::vector<int>> fourSum(std::vector<int> &num, int target) {
    std::sort(num.begin(), num.end());
    std::vector<int> next(num.size());
    for (int ix = num.size() - 1; ix >= 0; --ix) {
      if (ix == num.size() - 1 || num[ix] != num[ix + 1]) {
	next[ix] = ix + 1;
      } else {
	next[ix] = next[ix+1];
      }
    }
    std::vector<std::vector<int>> ans;
    // c + d  = target - (a + b)
    // enumerate a, b
    // then find all (c, d), this cost O(n)
    for (int a = 0; a < num.size(); a = next[a]) {
      for (int b = a + 1; b < num.size(); b = next[b]) {
	int _target = target - num[a] - num[b];
	for (int c = b + 1, d = num.size() - 1; c < d; c = next[c]) {
	  while (c < d && num[c] + num[d] > _target) {
	    -- d;
	  }
	  if (c < d && num[c] + num[d] == _target) {
	    ans.push_back(std::vector<int> {num[a], num[b], num[c], num[d]});
	  }
	}
      }
    }
    return ans;
  }
};
 
int main() {
  Solution  s;
  // auto num = std::vector<int>{1, 0, -1, 0, -2, 2};
  auto num = std::vector<int>{0, 0, 0, 0};
  for (auto &e : s.fourSum(num, 0)) {
    for (auto &x : e) {
      std::cout << x << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
