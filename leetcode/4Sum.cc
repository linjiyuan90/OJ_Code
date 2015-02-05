class Solution {
public:
  // O(n^3)
  vector<vector<int> > fourSum(vector<int> &num, int target) {
    std::sort(num.begin(), num.end());
    std::vector<std::vector<int>> ans;
    for (int a = 0, n = num.size(); a < n; ++a) {
      // nice remove duplicates
      if (a > 0 && num[a] == num[a-1]) {
	continue;
      }
      for (int b = a + 1; b < n; ++b) {
	if (b > a + 1 && num[b] == num[b-1]) {
	  continue;
	}
	for (int c = b + 1, d = n - 1; c < d; ++c) {
	  if (c > b + 1 && num[c] == num[c-1]) {
	    continue;
	  }
	  while (c < d && num[a] + num[b] + num[c] + num[d] > target) {
	    -- d;
	  }
	  if (c < d && num[a] + num[b] + num[c] + num[d] == target) {
	    ans.push_back({num[a], num[b], num[c], num[d]});
	  }
	}
      }
    }
    return ans;
  }
};
