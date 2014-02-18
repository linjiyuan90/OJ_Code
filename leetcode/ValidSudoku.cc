class Solution {
public:
  bool isValidSudoku(std::vector<std::vector<char>> &board) {
    for (int i = 0; i < 9; ++i) {
      std::vector<int> row_cnt(9, 0), col_cnt(9, 0), sub_cnt(9, 0);
      for (int j = 0; j < 9; ++j) {
	if (board[i][j] != '.') {
	  if (++row_cnt[board[i][j] - '1'] > 1) {
	    return false;
	  }
	}
	if (board[j][i] != '.') {
	  if (++col_cnt[board[j][i] - '1'] > 1) {
	    return false;
	  }
	}
	int r0 = i/3*3, c0 = i%3*3;
	if (board[r0 + j/3][c0 + j%3] != '.') {
	  if (++sub_cnt[board[r0 + j/3][c0 + j%3] - '1'] > 1) {
	    return false;
	  }
	}
      }
    }
    return true;
  }
};
