class Solution {
public:
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    std::vector<std::vector<std::string>> ans;
    std::vector<std::string> board;
    dfs(ans, board, n);
    return ans;
  }
  
private:
  void dfs(std::vector<std::vector<std::string>> &ans, 
	   std::vector<std::string> &board,
	   int n) {
    if (board.size() == n) {
      ans.push_back(board);
      return;
    }
    int r = board.size();
    // find the mask
    for (int j = 0; j < n; ++j) {
      bool ok = true;
      for (int i = 0; i < r; ++i) {
	if (board[i][j] == 'Q' || 
	    j+(r-i) < n && board[i][j+(r-i)] == 'Q' ||
	    j-(r-i) >= 0 && board[i][j-(r-i)] == 'Q') {
	  ok = false;
	  break;
	}
      }
      if (ok) {
	board.push_back(std::string(j, '.') + "Q" + std::string(n-j-1, '.'));
	dfs(ans, board, n);
	board.pop_back();
      }
    }
  }
};
