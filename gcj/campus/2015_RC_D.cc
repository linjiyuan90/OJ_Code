#include "iostream"
#include "vector"
#include "string"
#include "algorithm"
#include "cassert"

struct Tetromino {
  std::vector<int> off_;
  std::vector<int> len_;
  int n_;
  int maxi_, maxh_;
  
  Tetromino(const std::vector<int>& off, const std::vector<int>& len):
    off_(off), len_(len) {
    assert(off.size() == len.size());
    n_ = off.size();
    maxh_ = 0;
    for (int i = 0; i < n_; ++i) {
      if (maxh_ < off_[i] + len_[i]) {
        maxi_ = i;
        maxh_ = off_[i] + len_[i];
      }
    }
  }
  
  Tetromino rotate() {
    int m = 0;
    for (int i = 0; i < n_; ++i) {
      m = std::max(off_[i] + len_[i], m);
    }
    std::vector<int> off(m), len(m);
    for (int i = 0; i < m; ++i) {
      bool empty = true;
      for (int j = 0; j < n_; ++j) {
        if (off_[j] >= m - i || off_[j] + len_[j] < m-i) {
          if (empty) {
            ++off[i];
          } else {
            break;
          }
        } else {
          ++len[i];
          empty = false;
        }
      }
    }
    return Tetromino(off, len);
  }
  
  std::string toString() {
    std::string s;
    for (int i = 0; i < n_; ++i) {
      s += std::to_string(off_[i]) + "," + std::to_string(len_[i]) + " ";
    }
    return s;
  }
};

std::vector<Tetromino> tetrominos = {
  Tetromino({1, 0}, {2, 2}),
  Tetromino({0, 1}, {2, 2}),
  Tetromino({0, 0}, {3, 1}),
  Tetromino({0, 0}, {1, 3}),
  Tetromino({0, 0}, {2, 2}),
  Tetromino({0}, {4}),
  Tetromino({0, 0, 0}, {1, 2, 1})
};

/*
1   2   3   4   5   6   7

x    x  x    x  xx  x    x
xx  xx  x    x  xx  x   xxx
 x  x   xx  xx      x
                    x
*/

class Board {
  int w, h;
  std::vector<std::vector<int>> board;
public:
  Board(int w, int h): w(w), h(h), board(h, std::vector<int>(w)) {
  }
  bool add(const int t, const int r, const int x) {
    Tetromino te = tetrominos[t];
    for (int i = 0; i < r; ++i) {
      te = te.rotate();
    }
    int bot = 0;
    for (int xx = x, c = 0; c < te.n_; ++c, ++xx) {
      int y = h - 1;
      while (y >= 0 && board[y][xx] == 0) --y;
      ++y;
      bot = std::max(bot, y - te.off_[c]);
    }
    int top = bot + te.maxh_ - 1;
    if (top >= h) {
      return false;
    }
    // range [x, x + n) x [bot, top]
    for (int xx = x, c = 0; c < te.n_; ++c, ++xx) {
      for (int yy = bot + te.off_[c]; yy < bot + te.off_[c] + te.len_[c]; ++yy) {
        board[yy][xx] = 1;
      }
    }
    // clear lines in [bot, top]
    for (int y = top; y >= bot; --y) {
      if (isRowFull(y)) {
        std::fill(board[y].begin(), board[y].end(), 0);
      }
    }
    // fall down
    int numEmptyRows = 0;
    for (int y = bot; y < h; ++y) { // not only top!!
      bool isYEmpty = isRowEmpty(y);
      if (numEmptyRows != 0) {
        board[y-numEmptyRows] = board[y];
        std::fill(board[y].begin(), board[y].end(), 0);
      }
      if (isYEmpty) {
        ++numEmptyRows;
      }
    }
    return true;
  }
  
  bool isRowFull(int r) {
    return std::count(board[r].begin(), board[r].end(), 1) == w;
  }

  bool isRowEmpty(int r) {
    return std::count(board[r].begin(), board[r].end(), 1) == 0;
  }

  std::vector<std::string> toString() {
    std::vector<std::string> strs(h);
    for (int r = 0; r < h; ++r) {
      std::transform(board[r].begin(),
                     board[r].end(),
                     std::back_inserter(strs[r]),
                     [](int b) {
                       return b ? 'x' : '.';
                     });
    }
    std::reverse(strs.begin(), strs.end());
    return strs;
  }
  void print() {
    for (const auto& s : toString()) {
      std::cout << s << std::endl;
    }
  }
};

int main() {
  int T, t = 1, n, w, h;
  for (std::cin >> T; t <= T; ++t) {
    std::cout << "Case #" << t << ":" << std::endl;
    std::cin >> w >> h >> n;
    Board board(w, h);
    bool isGameOver = false;
    for (int i = 0, ti, ri, xi; i < n; ++i) {
      std::cin >> ti >> ri >> xi;
      if (!isGameOver && !board.add(ti-1, ri, xi)) {
        isGameOver = true;
      }
    }
    if (isGameOver) {
      std::cout << "Game Over!" << std::endl;
    } else {
      board.print();
    }
  }
  return 0;
}
