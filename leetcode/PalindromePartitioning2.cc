class Solution {
public:
  int minCut(string s) {
    // O(n^2) to calculate all the possible palindrome substrings
    // then find the min cut using dynamic programming
        
    using std::vector;
        
    int n = s.length();
    vector<int> minCut(n, n);
    // enumerate center
    for (int i = 0; i < n; ++i) {
      // i as center
      for (int j = 0; i-j >= 0 && i+j < n && s[i-j] == s[i+j]; ++j) {
	minCut[i+j] = std::min(minCut[i+j], i-j == 0 ? 0 : minCut[i-j-1] + 1);
      }
      // the middle of (i, i+1) as center
      for (int j = 0; i-j >= 0 && i+1+j < n && s[i-j] == s[i+1+j]; ++j) {
	minCut[i+1+j] = std::min(minCut[i+1+j], i-j == 0 ? 0 : minCut[i-j-1] + 1);
      }
    }
    return minCut[n-1];
  }
};
