#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>

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

  // whether there is an area which contains enough chars for word
  bool isEnough(int n, int m, 
                const vector<vector<char>>& board,
                const string& word) {
    map<char, int> charCnts;
    for (char ch : word) {
      ++charCnts[ch];
    }
    vector<vector<bool>> mark(n, vector<bool>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (charCnts.count(board[i][j]) > 0) {
          mark[i][j] = true;
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (mark[i][j]) {
          queue<Pos> que;
          que.push(Pos(i, j));
          mark[i][j] = false;
          map<char, int> cnts;
          while (!que.empty()) {
            Pos now = que.front();
            que.pop();
            ++cnts[board[now.x][now.y]];
            for (Pos next : now.next(n, m)) {
              if (mark[next.x][next.y]) {
                que.push(next);
                mark[next.x][next.y] = false;
              }
            }
          }
          bool ok = true;
          for (pair<char, int> w : charCnts) {
            if (cnts[w.first] < w.second) {
              ok = false;
              break;
            }
          }
          if (ok) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool judge(int n, int m, 
             const vector<vector<char>>& board, 
             const string& word,
             vector<vector<bool>>& mark,
             Pos now,
             int l) {
    if (l == word.size()) {
      return true;
    }
    for (Pos next : now.next(n, m)) {
      if (board[next.i][next.j] == word[l] && !mark[next.i][next.j]) {
        mark[next.i][next.j] = true;
        if (judge(n, m, board, word, mark, next, l+1)) {
          return true;
        }
        mark[next.i][next.j] = false;
      }
    }
    return false;
  }

  bool judge(const vector<vector<char>>& board, const string& word) {
    if (word.empty()) {
      return true;
    }
    if (board.empty()) {
      return false;
    }
    int n = board.size();
    int m = board.front().size();
    if (!isEnough(n, m, board, word)) {
      return false;
    }
    vector<vector<bool>> mark(n, vector<bool>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] == word.front()) {
          mark[i][j] = true;
          if (judge(n, m, board, word, mark, Pos(i, j), 1) {
            return true;
          }
          mark[i][j] = false;
        }
      }
    }
    return false;
  }

 public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    vector<string> ans;
    for (const string& word : words) {
      if (judge(board, word)) {
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

