class Solution {
  int di[4]{0, 1, 0, -1};
  int dj[4]{1, 0, -1, 0};
    
public:
  vector<int> spiralOrder(vector<vector<int> > &matrix) {
    std::vector<int> res;
    if (matrix.empty()) {
      return res;
    }
    int n = matrix.size(), m = matrix.front().size();
    int min_i = 0, max_i = n - 1;
    int min_j = 0, max_j = m - 1;
    for (int i = 0, j = 0, d = 0, c = 0; c < n * m; ++c) {
      res.push_back(matrix[i][j]);
      if (i + di[d] < min_i) {
	d = (d + 1) % 4;
	++ min_j;
      }
      if (i + di[d] > max_i) {
	d = (d + 1) % 4;
	-- max_j;
      }
      if (j + dj[d] < min_j) {
	d = (d + 1) % 4;
	-- max_i;
      }
      if (j + dj[d] > max_j) {
	d = (d + 1) % 4;
	++ min_i;
      }
      i += di[d];
      j += dj[d];
    }
    return res;
  }
};
