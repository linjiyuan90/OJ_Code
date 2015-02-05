class Solution {
public:
  bool searchMatrix(vector<vector<int> > &matrix, int target) {
    if (matrix.empty()) {
      return false;
    }
    // start from the right-upper corner
    int n = matrix.size(), m = matrix.front().size();
    for (int i = 0, j = m-1; i < n && j >= 0; ) {
      if (matrix[i][j] == target) {
	return true;
      }
      if (matrix[i][j] < target) {
	++ i;
      } else {
	-- j;
      }
    }
    return false;
  }
};
