class Solution {
public:
  // O(n^2)
  vector<vector<int> > threeSum(vector<int> &num) {
    std::sort(num.begin(), num.end());
    std::vector<std::vector<int>> ans;
    for (int a = 0, n = num.size(); a < n; ++a) {
      // prevent duplicates
      if (a > 0 && num[a] == num[a-1]) {
	continue;
      }
      for (int b = a + 1, c = n - 1; b < c; ++b) {
	if (b > a + 1 && num[b] == num[b-1]) {
	  continue;
	}
	while (b < c && num[a] + num[b] + num[c] > 0) {
	  -- c;
	}
	if (b < c && num[a] + num[b] + num[c] == 0) {
	  ans.push_back({num[a], num[b], num[c]});
	}
      }
    }
    return ans;
  }
};
