class Solution {
public:
  int totalNQueens(int n) {
    return dfs((1<<n) - 1, 0, 0);
  }

private:
  // it's a little complicated to memo
  // just dfs
  int dfs(int candidate, int left, int right) {
    if (candidate == 0) {
      return 1;
    }
    int ans = 0;
    for (int can = candidate & ~(left | right); can; can &= (can - 1)) {
      int cur = can & -can;
      ans += dfs(candidate ^ cur, (left | cur) << 1, (right | cur) >> 1);
    }
    return ans;
  }
};
