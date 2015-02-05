class Solution {
public:
  // r, r-2, r, r-2, r, ... 
  // |  /    |  /    |
  string convert(string s, int nRows) {
    if (nRows <= 1) {
      return s;
    }
    std::string ans;
    int n = s.size();
    int r = nRows;
    int m = 2*r - 2;
    for (int i = 0; i < r; ++i) {
      for (int j = i, k = (i/m + 1) * m - i; j < n; j += m, k += m) {
	ans += s[j];
	if (i != 0 && i != r - 1 && k < n) {
	  ans += s[k];
	}
      }
    }
    return ans;
  }
};
