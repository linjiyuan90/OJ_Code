class Solution {
    
  std::vector<int> di = {0, 1, 0, -1};
  std::vector<int> dj = {1, 0, -1, 0};
    
  bool isValid(int i, int j, int n, int m) {
    return 0 <= i && i < n && 0 <= j && j < m;
  }
    
  bool exist(std::vector<std::vector<char>>& board, 
	     std::vector<std::vector<bool>>& mark,
	     std::string word,
	     int i, 
	     int j, 
	     int cur) {
    if (cur == word.size()) {
      return true;
    }
    int n = board.size(), m = board.front().size();
    for (int k = 0; k < 4; ++k) {
      int ii = i + di[k], jj = j + dj[k];
      if (!isValid(ii, jj, n, m) 
	  || mark[ii][jj] 
	  || board[ii][jj] != word[cur]) {
	continue;
      }
      mark[ii][jj] = true;
      if (exist(board, mark, word, ii, jj, cur + 1)) {
	return true;
      }
      mark[ii][jj] = false;
    }
    return false;
  }
    
public:
  bool exist(vector<vector<char> > &board, string word) {
    if (word.empty()) {
      return true;
    }
    if (board.empty()) {
      return false;
    }
    int n = board.size(), m = board.front().size();
    std::vector<std::vector<bool>> mark(n, std::vector<bool>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
	if (board[i][j] != word.front()) {
	  continue;
	}
	mark[i][j] = true;
	if (exist(board, mark, word, i, j, 1)) {
	  return true;
	}
	mark[i][j] = false;
      }
    }
    return false;
  }
};
