class Solution {
public:
  void solveSudoku(std::vector<std::vector<char>> &board) {
    // assume board is legal

    // Each step, choose the most certain one
    vertical_uncertainty.assign(9, 0);
    horizontal_uncertainty.assign(9, 0);
    board_uncertainty.assign(9, 0);
    left.clear();
    for (int r = 0; r < 9; ++r) {
      for (int c = 0; c < 9; ++c) {
	if (board[r][c] == '.') {
	  ++vertical_uncertainty[c];
	  ++horizontal_uncertainty[r];
	  ++board_uncertainty[r/3*3+ c/3];
	  left.push_back(std::make_pair(r, c));
	}
      }
    }
    dfs(board);
  }

private:
  bool dfs(std::vector<std::vector<char>> &board) {
    if (left.empty()) {
      return true;
    }
    // find the most certain one
    std::vector<std::pair<int, int>>::iterator min_it;
    int min_score = INT_MAX;
    for (auto it = left.begin(); it != left.end(); ++it) {
      int r = it->first, c = it->second;
      int score = vertical_uncertainty[c] + horizontal_uncertainty[r] +
	board_uncertainty[r/3*3 + c/3];
      if (score < min_score) {
	min_score = score;
	min_it = it;
      }
    }
    auto r = min_it->first, c = min_it->second;
    left.erase(min_it);
    --vertical_uncertainty[c];
    --horizontal_uncertainty[r];
    --board_uncertainty[r/3*3+c/3];
    std::string NUM = "123456789";
    // using set is slow, it's better to use vector
    std::set<char> candidates(NUM.begin(), NUM.end());
    for (int i = 0; i < 9; ++i) {
      candidates.erase(board[r][i]);
      candidates.erase(board[i][c]);
      candidates.erase(board[r/3*3+i/3][c/3*3+i%3]);
    }
    for (auto ch : candidates) {
      board[r][c] = ch;
      if (dfs(board)) {
	return true;
      }
      board[r][c] = '.';
    }
    ++vertical_uncertainty[c];
    ++horizontal_uncertainty[r];
    ++board_uncertainty[r/3*3+c/3];
    left.push_back(std::make_pair(r, c));
    return false;
  }

  std::vector<int> vertical_uncertainty;
  std::vector<int> horizontal_uncertainty;
  std::vector<int> board_uncertainty;
  std::vector<std::pair<int, int>> left;
};

class Solution {
public:
  // The above solution is faster, but a little complicated
  // Just brute-force will also work
  void solveSudoku(std::vector<std::vector<char>> &board) {
    std::vector<std::pair<int, int>> pos;
    for (int r = 0; r < 9; ++r) {
      for (int c = 0; c < 9; ++c) {
	if (board[r][c] == '.') {
	  pos.push_back(std::make_pair(r, c));
	}
      }
    }
    dfs(board, 0, pos);
  }
  
private:
  bool dfs(std::vector<std::vector<char>> &board, 
	   int ix,
	   std::vector<std::pair<int, int>> &pos) {
    if (ix == pos.size()) {
      return true;
    }
    int r = pos[ix].first, c = pos[ix].second;
    // find candidates
    std::vector<int> num(9, 1);
    for (int i = 0; i < 9; ++i) {
      if (board[r][i] != '.') {
	num[board[r][i] - '1'] = 0;
      }
      if (board[i][c] != '.') {
	num[board[i][c] - '1'] = 0;
      }
      if (board[r/3*3+i/3][c/3*3+i%3] != '.') {
	num[board[r/3*3+i/3][c/3*3+i%3] - '1'] = 0;
      }
    }
    for (int i = 0; i < 9; ++i) {
      if (num[i] == 0) {
	continue;
      }
      board[r][c] = '1' + i;
      if (dfs(board, ix+1, pos)) {
	return true;
      }
      board[r][c] = '.';
    }
    return false;
  }
};
