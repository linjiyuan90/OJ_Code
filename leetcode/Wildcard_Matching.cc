#include "iostream"
#include "vector"
#include "cstring"

using namespace std;

class Solution {
public:
  // O(n*m) not pass?
  bool isMatch(const char *s, const char *p) {
    int n = strlen(p), m = strlen(s);
    // need to use scroll array
    vector<vector<bool>> dp(2, vector<bool>(m+1, false));
    int pre = 0, now = 1;
    dp[now][0] = true;
    for (int i = 1; i <= n; i++) {
      swap(pre, now);
      bool or_dp = (i == 1); // record or(dp[i-1][0..j])
      dp[now][0] = (dp[pre][0] && p[i-1] == '*'); // m may be 0
      for (int j = 1; j <= m; j++) {
	or_dp |= dp[pre][j];
	if (p[i-1] == '*') {
	  if (or_dp) {
	    fill(dp[now].begin() + j, dp[now].end(), true);
	    break;
	  }
	  dp[now][j] = or_dp;
	} else {
	  dp[now][j] = ((p[i-1] == '?' || p[i-1] == s[j-1]) &&
		      dp[pre][j-1]);
	}
      }
    }
    return dp[now][m];
  }
};

int main() {
  Solution sl;
  char s[1000], p[1000];
  // cin >> s >> p;
  s[0] = p[0] = 0;
  cout << sl.isMatch(s, p);
}
