class Solution {
public:
  vector<vector<int> > generate(int numRows) {
    std::vector<std::vector<int>> triangle;
    for (int i = 0; i < numRows; ++i) {
      triangle.push_back(std::vector<int>(i+1));
      triangle[i].front() = triangle[i].back() = 1;
      for (int j = 1; j < i; ++j) {
	triangle[i][j] = triangle[i-1][j] + triangle[i-1][j-1];
      }
    }
    return triangle;
  }
};
