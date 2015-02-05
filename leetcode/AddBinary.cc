class Solution {
public:
  string addBinary(string a, string b) {
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    std::string ans;
    int n = a.size(), m = b.size();
    int c = 0;
    for (int i = 0; i < std::max(n, m); ++i) {
      if (i < n) {
	c += a[i] - '0';
      }
      if (i < m) {
	c += b[i] - '0';
      }
      ans.push_back('0' + (c % 2));
      c /= 2;
    }
    if (c > 0) {
      ans.push_back('1');
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};
