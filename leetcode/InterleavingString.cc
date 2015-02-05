class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    size_t n = s1.size(), m = s2.size();
    if (n + m != s3.size()) {
      return false;
    }
    vector<vector<bool>> feasible(n + 1, vector<bool>(m + 1));
    feasible[0][0] = true;
    for (size_t i = 1; i <= n; ++i) {
      feasible[i][0] = feasible[i-1][0] && s1[i-1] == s3[i-1];
    }
    for (size_t j = 1; j <= m; ++j) {
      feasible[0][j] = feasible[0][j-1] && s2[j-1] == s3[j-1];
    }
    for (size_t i = 1; i <= n; ++i) {
      for (size_t j = 1; j <= m; ++j) {
        feasible[i][j] = 
          (feasible[i-1][j] && s1[i-1] == s3[i+j-1]) ||
          (feasible[i][j-1] && s2[j-1] == s3[i+j-1]);
      }
    }
    return feasible[n][m];
  }
};
