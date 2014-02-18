class Solution {
public:
  std::vector<std::vector<int>> generateMatrix(int n) {
    auto ans = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    for (int i = 1, x = 0, y = 0, d = 0, n2 = n * n; i <= n2; ++ i) {
      ans[x][y] = i;
      if (!isOk(x + dx[d], y + dy[d], n) || ans[x+dx[d]][y+dy[d]] != 0) {
	d = (d + 1) % 4;
      }
      x += dx[d];
      y += dy[d];
    }
    return ans;
  }

  bool isOk(int x, int y, int n) {
    return 0 <= x && x < n && 0 <= y && y < n;
  }
};
