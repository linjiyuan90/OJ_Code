#include "iostream"
#include "vector"

void verticalReverse(std::vector<std::vector<int>>& board) {
  std::size_t n = board.size();
  for (std::size_t j = 0; j < n; ++j) {
    for (std::size_t s = 0, e = n-1; s < e; ++s, --e) {
      std::swap(board[s][j], board[e][j]);
    }
  }
}

void horizontalReverse(std::vector<std::vector<int>>& board) {
  for (auto& row : board) {
    std::reverse(row.begin(), row.end());
  }
}

void moveUp(std::vector<std::vector<int>>& board) {
  std::size_t n = board.size();
  for (std::size_t j = 0, c; j < n; ++j) {
    bool last = true;
    c = 0;
    for (std::size_t i = 0; i < n; ++i) {
      if (board[i][j] == 0) {
        continue;
      }
      if (last) {
        board[c++][j] = board[i][j];
        last = false;
      } else {
        if (board[c-1][j] == board[i][j]) {
          board[c-1][j] *= 2;
          last = true;
        } else {
          board[c++][j] = board[i][j];
          last = false;
        }
      }
    }
    for (; c < n; ++c) {
      board[c][j] = 0;
    }
  }
}

void moveLeft(std::vector<std::vector<int>>& board) {
  std::size_t n = board.size();
  for (std::size_t i = 0, c; i < n; ++i) {
    bool last = true;
    c = 0;
    for (std::size_t j = 0; j < n; ++j) {
      if (board[i][j] == 0) {
        continue;
      }
      if (last) {
        board[i][c++] = board[i][j];
        last = false;
      } else {
        if (board[i][c-1] == board[i][j]) {
          board[i][c-1] *= 2;
          last = true;
        } else {
          board[i][c++] = board[i][j];
          last = false;
        }
      }
    }
    for (; c < n; ++c) {
      board[i][c] = 0;
    }
  }
}

void move(std::vector<std::vector<int>>& board, const std::string& direction) {
  if (direction == "up" || direction == "down") {
    if (direction == "down") {
      verticalReverse(board);
    }
    moveUp(board);
    if (direction == "down") {
      verticalReverse(board);
    }
  } else {
    if (direction == "right") {
      horizontalReverse(board);
    }
    moveLeft(board);
    if (direction == "right") {
      horizontalReverse(board);
    }
  }
}

int main() {
  int T, n, t = 1;
  std::string direction;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ":" << std::endl;
    std::cin >> n >> direction;
    std::vector<std::vector<int>> board(n, std::vector<int>(n));
    for (auto& row : board) {
      for (auto& col : row) {
        std::cin >> col;
      }
    }
    move(board, direction);
    for (auto& row : board) {
      bool first = true;
      for (auto& col : row) {
        if (!first) {
          std::cout << " ";
        }
        std::cout << col;
        first = false;
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
