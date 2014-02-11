class Solution {
public:
  std::vector<std::vector<int>> generate(int numRows) {
    std::vector<std::vector<int>> ans;
    for (int i = 0; i < numRows; ++i) {
      ans.push_back(std::vector<int>());
      for (int j = 0; j <= i; ++j) {
	int val = 1;
	if (j != 0 && j != i) {
	  val = ans[i-1][j-1] + ans[i-1][j];
	}
	ans[i].push_back(val);
      }
    }
    return ans;
  }
};
