class Solution {
  const std::vector<int> dx = {0, 1, 0, -1};
  const std::vector<int> dy = {1, 0, -1, 0};

  // dfs will lead to RE
  void mark_invalid(std::vector<std::vector<char>> &board, int x, int y) {
    if (board[x][y] != 'O') {
      return;
    }
    board[x][y] = '#';
    std::queue<std::pair<int, int>> Q;
    Q.push({x, y});
    while(!Q.empty()) {
      int x = Q.front().first, y = Q.front().second;
      Q.pop();
      for (int k = 0; k < 4; ++k) {
	int xx = x + dx[k];
	int yy = y + dy[k];
	if (0 <= xx && xx < board.size() 
	    && 0 <= yy && yy < board[0].size()
	    && board[xx][yy] == 'O') {
	  board[xx][yy] = '#';
	  Q.push({xx, yy});
	}
      }
    }
  }
    
public:
  void solve(vector<vector<char>> &board) {
    // check the boundary
    for (int x = 0; x < board.size(); ++x) {
      for (int y = 0; y < board[0].size(); ++y) {
	if (x == 0 || x == board.size() - 1 
	    || y == 0 || y == board[0].size() - 1) {
	  mark_invalid(board, x, y);
	}
      }
    }
    for (int x = 0; x < board.size(); ++x) {
      for (int y = 0; y < board[0].size(); ++y) {
	if (board[x][y] == 'O') {
	  board[x][y] = 'X';
	}
	if (board[x][y] == '#') {
	  board[x][y] = 'O';
	}
      }
    }
  }
};
