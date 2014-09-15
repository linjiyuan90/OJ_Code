/*
  Given a board of '#' and '.', find a path from (sx, sy) to (ex, ey)
  where each step of the path must have a '#' in its left side.

  There is only one path since every step needs a '#' in its left side.
*/
#include "iostream"
#include "vector"
#include "string"
#include "queue"
#include "functional"
#include "tuple"

const int MaxSteps = 10000;

struct Direction {
  int dx, dy;
  char d;
};

const std::vector<Direction> Directions = {
  {0, 1, 'E'},
  {1, 0, 'S'},
  {0, -1, 'W'},
  {-1, 0, 'N'},
};

std::pair<bool, std::string> edisonRun(const std::vector<std::string>& board,
                                       int sx, int sy,
                                       int ex, int ey) {
  std::string routes;
  for (int x = sx, y = sy, s = 0, lastD = -1; s <= MaxSteps; ++s) {
    if (x == ex && y == ey) {
      return {true, routes};
    }
    bool noway = true;
    for (std::size_t c = 0, d = std::max(0, lastD); c < 4; ++c, d = (d+1)%4) {
      // before move forward, make sure the left side is #
      int lx = x + Directions[(d+3)%4].dx, ly = y + Directions[(d+3)%4].dy;
      if (board[lx][ly] != '#') {
        continue;
      }
      int xx = x + Directions[d].dx, yy = y + Directions[d].dy;
      lx = xx + Directions[(d+3)%4].dx, ly = yy + Directions[(d+3)%4].dy;
      if (board[xx][yy] == '.') {
        // exception here
        if (xx == ex && yy == ey) {
          return {true, routes + Directions[d].d};
        }
        // walk
        if (board[lx][ly] == '#') {
          x = xx;
          y = yy;
          routes.push_back(Directions[d].d);
          lastD = d;
          noway = false;
          break;
        }
        // turn around
        if (board[lx][ly] == '.') {
          x = lx;
          y = ly;
          routes.push_back(Directions[d].d);
          routes.push_back(Directions[(d+3)%4].d);
          lastD = (d+3)%4;
          noway = false;
          break;
        }
      }
    }
    if (noway) {
      break;
    }
  }
  return {false, ""};
}

int main() {
  int T, t = 1, n;
  for (std::cin >> T; T-- && std::cin >> n; ++t) {
    std::cout << "Case #" << t << ": ";
    std::vector<std::string> board(n+2);
    board.front().assign(n+2, '#');
    board.back().assign(n+2, '#');
    for (int i = 1; i <= n; ++i) {
      std::cin >> board[i];
      board[i].resize(n+2, '#');
      std::rotate(board[i].begin(), board[i].begin()+n, board[i].begin()+n+1);
    }
    int sx, sy, ex, ey;
    std::cin >> sx >> sy >> ex >> ey;
    auto res = edisonRun(board, sx, sy, ex, ey);
    if (res.first) {
      std::cout << res.second.size() << std::endl << res.second << std::endl;
    } else {
      std::cout << "Edison ran out of energy." << std::endl;
    }
  }
  return 0;
}
