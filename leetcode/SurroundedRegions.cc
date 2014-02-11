class Solution {
public:
  // floodfill
  // mark all these 'O' to 'z' if there exists some bounded 'O'
  // fill all the left 'O' to '#'
  // restore the 'O'
  // the recursive fill will lead to stackoverflow
  void solve(std::vector<std::vector<char>> &board) {
    if (board.empty()) {
      return;
    }
    
    // mark the bounded 'O' to '#'
    for (int x = 0; x < board.size(); ++x) {
      bfs(board, x, 0, 'O', '#');
      bfs(board, x, board[0].size() - 1, 'O', '#');
    }
    for (int y = 0; y < board[0].size(); ++y) {
      bfs(board, 0, y, 'O', '#');
      bfs(board, board.size() - 1, y, 'O', '#');
    }
    // fill these 'O' to 'X', and restore '#'
    for (auto &row : board) {
      for (auto &col : row) {
	if (col == 'O') {
	  col = 'X';
	}
	if (col == '#') {
	  col = 'O';
	}
      }
    }
  }
  
  // change (x, y) and its neighbors to color t if they are color s
  void bfs(std::vector<std::vector<char>> &board,
	   int x, int y, char s, char t) {
    if (board[x][y] != s) {
      return;
    }
    board[x][y] = t;
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(x, y));
    while (!q.empty()) {
      x = q.front().first;
      y = q.front().second;
      q.pop();
      int dx[] = {-1, 0, 1, 0};
      int dy[] = {0, 1, 0, -1};
      for (int k = 0; k < 4; ++k) {
	int xx = x + dx[k];
	int yy = y + dy[k];
	if (0 <= xx && xx < board.size() &&
	    0 <= yy && yy < board[0].size() &&
	    board[xx][yy] == s) {
	  board[xx][yy] = t;
	  q.push(std::make_pair(xx, yy));
	}
      }
    }
  }
};
