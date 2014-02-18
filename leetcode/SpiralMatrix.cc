class Solution {
public:
  std::vector<int> spiralOrder(std::vector<std::vector<int>> &matrix) {
    std::vector<int> ans;
    if (!matrix.empty()) {
      int n = matrix.size(), m = matrix[0].size();
      int dx[] = {0, 1, 0, -1};
      int dy[] = {1, 0, -1, 0};
      int lx = 0, rx = n - 1, ly = 0, ry = m-1;
      for (int x = 0, y = 0, k = 0, c = 0; c < n*m ; ++c) {
	ans.push_back(matrix[x][y]);
	int xx = x + dx[k];
	int yy = y + dy[k];
	if (xx < lx || xx > rx || yy < ly || yy > ry) {
	  if (k == 0) {
	    ++lx;
	  } else if (k == 1) {
	    --ry;
	  } else if (k == 2) {
	    --rx;
	  } else if (k == 3) {
	    ++ly;
	  }
	  k = (k + 1) % 4;
	  xx = x + dx[k];
	  yy = y + dy[k];
	}
	x = xx;
	y = yy;
      }
    }
    return ans;
  }
};
