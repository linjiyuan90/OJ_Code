#include "iostream"
#include "string"
#include "vector"

int di[] = {0, 0, 1, 1, 1, -1, -1, -1};
int dj[] = {1, -1, -1, 0, 1, -1, 0, 1};

// need to memo, since the neighbors only need be count once
int countNeighbor(const std::vector<std::string>& board, int i, int j) {
  int n = board.size();
  int cnt = 0;
  for (int k = 0; k < 8; ++k) {
    int ii = i + di[k], jj = j + dj[k];
    if (ii >= 0 && ii < n && jj >= 0 && jj < n && board[ii][jj] == '*') {
      ++cnt;
    }
  }
  return cnt;
}

void spread(std::vector<std::string>& board, int i, int j) {
  int n = board.size();
  board[i][j] = 'x';
  if (countNeighbor(board, i, j) == 0) {
    for (int k = 0; k < 8; ++k) {
      int ii = i + di[k], jj = j + dj[k];
      if (ii >= 0 && ii < n && jj >= 0 && jj < n && board[ii][jj] == '.') {
        spread(board, ii, jj);
      }
    }
  }
}

// Keypoint: in a connected component, choose any cell that has zero '*' neighbors has same effect
// So, at each time, choose the cell with minimal '*' neighbors
int minClick(std::vector<std::string> board) {
  int n = board.size();
  int clicks = 0;
  while(true) {
    int min = -1;
    int minI, minJ;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == '.') {
          int c = countNeighbor(board, i, j);
          if (min == -1 || c < min) {
            min = c;
            minI = i;
            minJ = j;
          }
        }
      }
    }
    if (min == -1) {
      break;
    }
    ++clicks;
    // spread
    spread(board, minI, minJ);
  }
  return clicks;
}
  
int main() {
  int T, t = 1, n;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n;
    std::vector<std::string> board(n);
    for (auto& line : board) {
      std::cin >> line;
    }
    std::cout << minClick(board) << std::endl;
  }
  return 0;
}
