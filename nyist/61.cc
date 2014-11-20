#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

int calcMaxScore(const vector< vector<int> >& grid) {
  // dp[k][i][j]
  // k steps, 
  // where the upper one move i right steps, the lower one move j right steps
  int n = grid.size(), m = grid.front().size();
  int MaxStep = n - 2 + m - 1;
  vector< vector< vector<int> > > dp(MaxStep + 1, 
                                     vector< vector<int> > (m, vector<int>(m, numeric_limits<int>::min())));
  dp[1][1][0] = grid[0][1] + grid[1][0];
  for (int l = 2; l <= MaxStep; ++l) {
    for (int i = 0; i <= l && i < m; ++i) {
      for (int j = 0; j <= l && j < m; ++j) {
        if (i <= j || l - i >= n || l - j >= n) {
          continue;
        }
        dp[l][i][j] = max(dp[l][i][j], dp[l-1][i][j] + grid[l-i][i] + grid[l-j][j]);
        if (i > 0) {
          dp[l][i][j] = max(dp[l][i][j], dp[l-1][i-1][j] + grid[l-i][i] + grid[l-j][j]);
        }
        if (j > 0) {
          dp[l][i][j] = max(dp[l][i][j], dp[l-1][i][j-1] + grid[l-i][i] + grid[l-j][j]);
        }
        if (i > 0 && j > 0) {
          dp[l][i][j] = max(dp[l][i][j], dp[l-1][i-1][j-1] + grid[l-i][i] + grid[l-j][j]);
        }
      }
    }
  }
  return dp[MaxStep][m-1][m-2];
}

int main() {
  int T, n, m;
  for (cin >> T; T--;) {
    cin >> n >> m;
    vector< vector<int> > grid(n, vector<int>(m));
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < m; ++c) {
        cin >> grid[r][c];
      }
    }
    cout << calcMaxScore(grid) << endl;
  }
  return 0;
}
