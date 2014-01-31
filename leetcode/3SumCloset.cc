#include "iostream"
#include "vector"

class Solution {
public:
  int threeSumClosest(std::vector<int> &num, int target) {
    std::sort(num.begin(), num.end());
    int ans = INT_MAX - abs(target);
    for (int a = 0; a < num.size(); ++a) {
      for (int b = a + 1, c = num.size() - 1; b < c; ++b) {
	while (b < c && num[a] + num[b] + num[c] > target) {
	  update(ans, target, num[a] + num[b] + num[c]);
	  --c;
	}
	if (b < c) {
	  update(ans, target, num[a] + num[b] + num[c]);
	}					      
      }
    }
    return ans;
  }
private:
  void update(int &ans, int target, int now) {
    if (abs(ans - target) > abs(target - now)) {
      ans = now;
    }
  }
};
