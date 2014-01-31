#include "iostream"
#include "vector"

class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int> &num) {
    std::sort(num.begin(), num.end());
    std::vector<std::vector<int>> ans;
    for (int a = 0; a < num.size(); ++a) {
      if (a > 0 && num[a] == num[a-1]) {
	continue;
      }
      for (int b = a + 1, c = num.size() - 1; b < c; ++b) {
	if (b > a + 1 && num[b] == num[b-1]) {
	  continue;
	}
	while (b < c && num[a] + num[b] + num[c] > 0) {
	  --c;
	}
	if (b < c && num[a] + num[b] + num[c] == 0) {
	  ans.push_back(std::vector<int>{num[a], num[b], num[c]});
	}					      
      }
    }
    return ans;
  }
};
