class Solution {
  const vector<int> dr = {0, 1, 0, -1};
  const vector<int> dc = {1, 0, -1, 0};
    
public:
  vector<vector<int> > generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    int maxR = n - 1, minR = 0;
    int maxC = n - 1, minC = 0;
    for (int x = 1, r = 0, c = 0, d = 0; x <= n * n; ++x) {
      matrix[r][c] = x;
      if (r + dr[d] > maxR) {
        -- maxC;
        d = (d + 1) % 4;
      } else if (r + dr[d] < minR) {
        ++ minC;
        d = (d + 1) % 4;
      } else if (c + dc[d] > maxC) {
        ++ minR;
        d = (d + 1) % 4;
      } else if (c + dc[d] < minC) {
        -- maxR;
        d = (d + 1) % 4;
      }
      r += dr[d];
      c += dc[d];
    }
    return matrix;
  }
};
