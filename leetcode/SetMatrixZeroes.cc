class Solution {
public:
  void setZeroes(std::vector<std::vector<int>> &matrix) {
    if (matrix.empty()) {
      return;
    }
    // use the first row to record all column zeros
    int n = matrix.size(), m = matrix[0].size();
    bool first_row = 
      std::find(matrix[0].begin(), matrix[0].end(), 0) != matrix[0].end();
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
	if (matrix[i][j] == 0) {
	  matrix[0][j] = 0;
	}
      }
      bool zero =
	std::find(matrix[i].begin(), matrix[i].end(), 0) != matrix[i].end();
      if (zero) {
	matrix[i].assign(m, 0);
      }
    }
    for (int j = 0; j < m; ++j) {
      if (matrix[0][j] == 0) {
	for (int i = 0; i < n; ++i) {
	  matrix[i][j] = 0;
	}
      }
    }
    if (first_row) {
      matrix[0].assign(m, 0);
    }
  }
};
