class Solution {
  int totalNQueens(int r, int n, int left, int horizontal, int right) {
    if (r == n) {
      return 1;
    }    
    // enumerate all possible ways
    int ways = 0;
    int all = (1<<n) - 1;
    int possible = all ^ (left | horizontal | right);
    for (int i = 0, k=1; i < n; ++i, k<<=1) {
      if (possible & k) {
        ways += totalNQueens(r+1, n , (left|k)<<1, horizontal|k, (right|k)>>1);
      }
    }
    return ways;
  }
    
public:
  int totalNQueens(int n) {
    // the memo approach seems cost lots of memory
    // so just use dfs to count it
    return totalNQueens(0, n, 0, 0, 0);
  }
};
