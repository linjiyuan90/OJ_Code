class Solution {
public:
  void setZeroes(vector<vector<int> > &matrix) {
    if (matrix.empty()) {
      return;
    }
    int n = matrix.size(), m = matrix[0].size();
    bool first_row_zero = 
      std::find(matrix[0].begin(), matrix[0].end(), 0) != matrix[0].end();
    for (int i = 1; i < n; ++i) {
      bool has_zero = false;
      for (int j = 0; j < m; ++j) {
	if (matrix[i][j] == 0) {
	  matrix[0][j] = 0;
	  has_zero = true;
	}
      }
      if (has_zero) {
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
    if (first_row_zero) {
      matrix[0].assign(m, 0);
    }
  }
};
