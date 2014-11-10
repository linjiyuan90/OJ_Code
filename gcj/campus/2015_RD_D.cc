#include <cstdlib>
#include <cassert>
#include <cmath>

#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

const int MaxBound = 8;

typedef pair<int, int> Position;

int sign(int x) {
  return x < 0 ? -1 : x > 0;
}

class Piece {
public:
  Position pos;
public:
  Piece(const string& str) {
    char x;
    int y;
    sscanf (str.c_str(), "%c%d-%*c", &x, &y);
    pos = {x - 'A' + 10, y};
  }
  virtual vector<bool> canKill(const vector<Piece*>& that) = 0;
};

class King : public Piece {
public:
  King(const string& str) : Piece(str) {
  }
  virtual vector<bool> canKill(const vector<Piece*>& that) {
    vector<bool> kill(that.size());
    for (size_t i = 0; i < that.size(); ++i) {
      Piece* pt = that[i];
      if (pt == this) {
        continue;
      }
      if (abs(pt->pos.first - pos.first) <= 1 &&
          abs(pt->pos.second - pos.second) <= 1) {
        kill[i] = true;
      }
    }
    return kill;
  }
};

class Queen : public Piece {
public:
  Queen(const string& str) : Piece(str) {
  }
  virtual vector<bool> canKill(const vector<Piece*>& that) {
    vector<bool> kill(that.size());
    map<pair<int, int>, pair<int, int>> cand;
    for (size_t i = 0; i < that.size(); ++i) {
      Piece* pt = that[i];
      if (pt == this) {
        continue;
      }
      pair<int, int> dir = {
        sign(pt->pos.first - pos.first),
        sign(pt->pos.second - pos.second)
      };
      int dx = abs(pt->pos.first - pos.first);
      int dy = abs(pt->pos.second - pos.second);
      if (dx != 0 && dy != 0 && dx != dy) {
        continue;
      }
      int d = dx == dy ? dx : dx + dy;
      if (cand.count(dir)) {
        if (cand[dir].first > d) {
          kill[cand[dir].second] = false;
          kill[i] = true;
          cand[dir] = {d, i};
        }
      } else {
        kill[i] = true;
        cand[dir] = {d, i};
      }
    }
    return kill;
  }
};

class Rook : public Piece {
public:
  Rook(const string& str) : Piece(str) {
  }
  virtual vector<bool> canKill(const vector<Piece*>& that) {
    vector<bool> kill(that.size());
    map<pair<int, int>, pair<int, int>> cand;
    for (size_t i = 0; i < that.size(); ++i) {
      Piece* pt = that[i];
      if (pt == this) {
        continue;
      }
      pair<int, int> dir = {
        sign(pt->pos.first - pos.first),
        sign(pt->pos.second - pos.second)
      };
      if (!(dir.first == 0 || dir.second == 0)) {
        continue;
      }
      int d = abs(pt->pos.first - pos.first) + abs(pt->pos.second - pos.second);
      if (cand.count(dir)) {
        if (cand[dir].first > d) {
          kill[cand[dir].second] = false;
          kill[i] = true;
          cand[dir] = {d, i};
        }
      } else {
        kill[i] = true;
        cand[dir] = {d, i};
      }
    }
    return kill;
  }
};

class Bishop : public Piece {
public:
  Bishop(const string& str) : Piece(str) {
  }
  virtual vector<bool> canKill(const vector<Piece*>& that) {
    vector<bool> kill(that.size());
    map<pair<int, int>, pair<int, int>> cand;
    for (size_t i = 0; i < that.size(); ++i) {
      Piece* pt = that[i];
      if (pt == this) {
        continue;
      }
      pair<int, int> dir = {
        sign(pt->pos.first - pos.first),
        sign(pt->pos.second - pos.second)
      };
      if (dir.first == 0 || dir.second == 0 ||
          abs(pt->pos.first - pos.first) != abs(pt->pos.second - pos.second)) {
        continue;
      }
      int d = abs(pt->pos.first - pos.first);
      if (cand.count(dir)) {
        if (cand[dir].first > d) {
          kill[cand[dir].second] = false;
          kill[i] = true;
          cand[dir] = {d, i};
        }
      } else {
        kill[i] = true;
        cand[dir] = {d, i};
      }
    }
    return kill;
  }
};

class Knight : public Piece {
public:
  Knight(const string& str) : Piece(str) {
  }
  virtual vector<bool> canKill(const vector<Piece*>& that) {
    vector<bool> kill(that.size());
    for (size_t i = 0; i < that.size(); ++i) {
      Piece* pt = that[i];
      if (pt == this) {
        continue;
      }
      if ((abs(pt->pos.first - pos.first) == 2 && abs(pt->pos.second - pos.second) == 1) ||
          (abs(pt->pos.first - pos.first) == 1 && abs(pt->pos.second - pos.second) == 2)) {
        kill[i] = true;
      }
    }
    return kill;
  }
};

class Pawn : public Piece {
public:
  Pawn(const string& str) : Piece(str) {
  }
  virtual vector<bool> canKill(const vector<Piece*>& that) {
    vector<bool> kill(that.size());
    for (size_t i = 0; i < that.size(); ++i) {
      Piece* pt = that[i];
      if (pt == this) {
        continue;
      }
      kill[i] = 
        pt->pos.first - pos.first == 1 && 
        abs(pt->pos.first - pos.first) == abs(pt->pos.second - pos.second);
    }
    return kill;
  }
};

Piece* createPiece(const string& str) {
  switch (str.back()) {
    case 'K' : return new King(str);
    case 'Q' : return new Queen(str);
    case 'R' : return new Rook(str);
    case 'B' : return new Bishop(str);
    case 'N' : return new Knight(str);
    case 'P' : return new Pawn(str);
  }
  return NULL;
}

int main() {
  int T, t = 1, n;
  string str;
  for (cin >> T; T--; t++) {
    cout << "Case #" << t << ": ";
    cin >> n;
    vector<Piece*> pieces(n);
    for (int i = 0; i < n; ++i) {
      cin >> str;
      pieces[i] = createPiece(str);
    }
    int totalWays = 0;
    for (size_t i = 0; i < n; ++i) {
      auto thatKill = pieces[i]->canKill(pieces);
      // copy(thatKill.begin(), thatKill.end(), ostream_iterator<bool>(cout, " "));
      // cout << endl;
      totalWays += count(thatKill.begin(), thatKill.end(), true);
    }
    cout << totalWays << endl;
  }
  return 0;
}
