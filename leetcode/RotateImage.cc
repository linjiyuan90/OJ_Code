class Solution {
public:
  void rotate(vector<vector<int> > &matrix) {
    int n = matrix.size();
    // enumerate each 'ring'
    for (int i = 0, l = n - 1; i < n/2; ++i, l -= 2) {
      for (int j = 0; j < l; ++j) {
	std::swap(matrix[i][i+j], matrix[i+j][i+l]);
	std::swap(matrix[i][i+j], matrix[i+l][i+l-j]);
	std::swap(matrix[i][i+j], matrix[i+l-j][i]);
      }
    }
  }
};
