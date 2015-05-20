#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

struct Pos {
  int x, y;
  Pos(): Pos(-1, -1) {}
  Pos(int x, int y): x(x), y(y) {}
  vector<Pos> next(int n, int m) {
    vector<Pos> next;
    for (int k = 0; k < 4; ++k) {
      int xx = x + dx[k], yy = y + dy[k];
      if (0 <= xx && xx < n && 0 <= yy && yy < m) {
        next.push_back(Pos(xx, yy));
      }
    }
    return next;
  }
  
  bool operator != (const Pos& that) const {
    return x != that.x || y != that.y;
  }
};

class Solution {

  bool biJudge(int n, int m,
               const vector<vector<char>>& board, 
               const string& word, 
               vector<vector<bool>>& mark,
               Pos a, Pos b, int l, int r) {
    if (l == -1 && r == word.size()) {
      return true;
    }
    if (l == -1) {
      for (Pos nb : b.next(n, m)) {
        if (board[nb.x][nb.y] == word[r]) {
          mark[nb.x][nb.y] = true;
          if (biJudge(n, m, board, word, mark, a, nb, l, r + 1)) {
            return true;
          }
          mark[nb.x][nb.y] = false;
        }
      }
      return false;
    } else if (r == word.size()) {
      for (Pos na : a.next(n, m)) {
        if (board[na.x][na.y] == word[l]) {
          mark[na.x][na.y] = true;
          if (biJudge(n, m, board, word, mark, na, b, l-1, r)) {
            return true;
          }
          mark[na.x][na.y] = false;
        }
      }
      return false;
    } else {
      for(Pos na : a.next(n, m)) {
        for (Pos nb: b.next(n, m)) {
          if (na != nb && board[na.x][na.y] == word[l] && board[nb.x][nb.y] == word[r]) {
            mark[na.x][na.y] = true;
            mark[nb.x][nb.y] = true;
            if (biJudge(n, m, board, word, mark, na, nb, l-1, r+1)) {
              return true;
            }
            mark[na.x][na.y] = false;
            mark[nb.x][nb.y] = false;
          }
        }
      }
      return false;
    }
  }
  
  bool biJudge(int n, int m,
               const vector<vector<char>>& board, 
               const string& word, 
               vector<vector<bool>>& mark) {
    int l = word.size() / 2, r = l + 1;
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        if (board[x][y] == word[l]) {
          if (word.size() == 1) {
            return true;
          }
          Pos a(x, y);
          for (Pos b: a.next(n, m)) {
            if (board[b.x][b.y] == word[r]) {
              mark[a.x][a.y] = true;
              mark[b.x][b.y] = true;
              if (biJudge(n, m, board, word, mark, a, b, l-1, r+1)) {
                return true;
              }
              mark[a.x][a.y] = false;
              mark[b.x][b.y] = false;
            }
          }
        }
      }
    }
    return false;
  }

  bool biJudge(const vector<vector<char>>& board, const string& word) {
    if (word.empty()) {
      return true;
    }
    if (board.empty()) {
      return false;
    }
    int n = board.size();
    int m = board.front().size();
    vector<vector<bool>> mark(n, vector<bool>(m));
    return biJudge(n, m, board, word, mark);
  }

 public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    vector<string> ans;
    for (const string& word : words) {
      if (biJudge(board, word)) {
        ans.push_back(word);
      }
    }
    return ans;
  } 
};


int main() {
  vector<string> boardString = {
    //     "oaan", "etae", "ihkr", "iflv"
    "aaaa","aaaa","aaaa","aaaa","bcde","fghi","jklm","nopq","rstu","vwxy","zzzz"
  };
  vector<vector<char>> board;
  transform(boardString.begin(), boardString.end(), back_inserter(board), [](const string& word) {
      return vector<char>(word.begin(), word.end());
    });
  // vector<string> words = { "oath", "pea", "eat", "rain" };
  // vector<string> words = { "aaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaab","aaaaaaaaaaaaaaac","aaaaaaaaaaaaaaad","aaaaaaaaaaaaaaae","aaaaaaaaaaaaaaaf","aaaaaaaaaaaaaaag","aaaaaaaaaaaaaaah","aaaaaaaaaaaaaaai","aaaaaaaaaaaaaaaj","aaaaaaaaaaaaaaak","aaaaaaaaaaaaaaal","aaaaaaaaaaaaaaam","aaaaaaaaaaaaaaan","aaaaaaaaaaaaaaao","aaaaaaaaaaaaaaap","aaaaaaaaaaaaaaaq","aaaaaaaaaaaaaaar","aaaaaaaaaaaaaaas","aaaaaaaaaaaaaaat","aaaaaaaaaaaaaaau","aaaaaaaaaaaaaaav","aaaaaaaaaaaaaaaw"};
  vector<string> words = { "aaaaaaaaaaaaaaaw" };
  Solution sol;
  for (const string& ans : sol.findWords(board, words)) {
    cout << ans << endl;
  }
  return 0;
}

