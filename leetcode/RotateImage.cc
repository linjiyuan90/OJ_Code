class Solution {
public:
  void rotate(std::vector<std::vector<int>> &matrix) {
    int n = matrix.size();
    for (int i = 0; i < n/2; ++i) {
      for (int j = i; j < n-1-i; ++j) {
	std::swap(matrix[i][j], matrix[j][n-1-i]);
	std::swap(matrix[i][j], matrix[n-1-i][n-1-j]);
	std::swap(matrix[i][j], matrix[n-1-j][i]);
      }
    }
  }
};
