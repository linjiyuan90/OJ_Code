class Solution {
public:
  std::string addBinary(std::string a, std::string b) {
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    int n = std::max(a.length(), b.length());
    a.resize(n, '0');
    b.resize(n, '0');
    int c = 0;
    for (size_t i = 0; i < n; ++i) {
      c = c + (a[i] == '1') + (b[i] == '1');
      a[i] = c % 2 + '0';
      c = c / 2;
    }
    if (c != 0) {
      a.push_back('1');
    }
    std::reverse(a.begin(), a.end());
    return a;
  }
};
