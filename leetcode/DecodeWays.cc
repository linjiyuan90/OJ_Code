class Solution {
public:
  int numDecodings(string s) {
    if (s.empty()) {
      return 0;
    }
    // cnt[i]: the number of ways to decode s[0..i]
    // cnt[i] = cnt[i-1] + (if avaiable, cnt[i-2])
    // note the '0'
    int n = s.size();
    std::vector<int> cnt(n+1);
    cnt[0] = 1;
    for (int i = 0; i < n; ++i) {
      if (s[i] != '0') {
        cnt[i+1] += cnt[i];
      }
      if (i >= 1 && s[i-1] != '0') {
        int v = std::stoi(s.substr(i-1, 2));
        if (1 <= v && v <= 26) {
          cnt[i+1] += cnt[i-1];
        }
      }
    }
    return cnt[n];
  }
};
