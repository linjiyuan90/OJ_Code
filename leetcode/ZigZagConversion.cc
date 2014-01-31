#include "iostream"
#include "algorithm"
#include "vector"
#include "string"

class Solution {
public:
  // TODO
  // instead of filling the matrix
  // output to string directly
  std::string convert(std::string s, int nRows) {
    std::vector<std::string> cols;
    for (size_t ix = 0; ix < s.length();) {
      // down
      int len = std::min(nRows, (int)(s.length() - ix));
      std::string col = s.substr(ix, len) + std::string(nRows - len, ' ');
      cols.push_back(col);
      ix += len;  // don't forget

      // up (at most nRows-2 columns)
      for (int c = 0; ix < s.length() && c < nRows - 2; ++c) {
	std::string col = std::string(nRows, ' ');
	col[nRows - 2 - c] = s[ix++];
	cols.push_back(col);
      }
    }
    std::string res;
    for (int r = 0, nCols = cols.size(); r < nRows; ++r) {
      // how to use filter?
      for (int c = 0; c < nCols; ++c) {
	if (cols[c][r] != ' ') {
	  res += cols[c][r];
	}
      }
    }
    return res;
  }
};


int main() {
  Solution sol;
  std::cout << sol.convert("PAYPALISHIRING", 3) << std::endl;
}
