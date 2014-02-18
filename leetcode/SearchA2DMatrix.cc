class Solution {
public:
  bool searchMatrix(std::vector<std::vector<int>> &matrix, int target) {
    if (matrix.empty()) {
      return false;
    }
    int n = matrix.size(), m = matrix[0].size();
    int lo = 0, hi = n*m;
    while (lo < hi) {
      int mi = (lo + hi) / 2;
      int r = mi/m, c = mi%m;
      if (matrix[r][c] == target) {
	return true;
      }
      if (matrix[r][c] < target) {
	lo = mi + 1;
      } else {
	hi = mi;
      }
    }
    return false;
    // return lo < n*m && matrix[lo/m][lo%m] == target;
  }
};
