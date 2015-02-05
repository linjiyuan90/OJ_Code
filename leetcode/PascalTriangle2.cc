class Solution {
public:
  vector<int> getRow(int rowIndex) {
    // t[i][j] = t[i-1][j] + t[i-1][j-1]
    std::vector<int> triangle(rowIndex + 1);
    triangle[0] = 1;
    for (int i = 1; i <= rowIndex; ++i) {
      triangle[i] = 1;
      for (int j = i-1; j > 0; --j) {
	triangle[j] += triangle[j-1];
      }
    }
    return triangle;
  }
};
