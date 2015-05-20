#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <queue>

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


struct TrieNode {
  TrieNode* children[26];
  // current node is a match node or not
  int match;
  // children has a match
  bool has;
  
  void insert(const string& word, int cur) {
    if (cur == word.size()) {
      ++match;
      has = true;
      return;
    }
    int ch = word[cur] - 'a';
    if (children[ch] == NULL) {
      children[ch] = new TrieNode();
    }
    children[ch]->insert(word, cur + 1);
    has = true;
  } 
};

class Solution {

  void findWords(int n, int m,
                 vector<vector<char>>& board, 
                 vector<vector<bool>>& mark,
                 Pos cur,
                 TrieNode* root,
                 string& path,
                 vector<string>& res) {
    int ch = board[cur.x][cur.y] - 'a';
    root = root->children[ch];
    if (root == NULL) {
      return;
    }
    mark[cur.x][cur.y] = true;
    path.push_back(board[cur.x][cur.y]);
    if (root->match > 0) {
      res.insert(res.end(), 1, path);
      root->match = 0;
    }
    for (Pos next : cur.next(n, m)) {
      if (!mark[next.x][next.y]) {
        findWords(n, m, board, mark, next, root, path, res);
      }
    }
    path.pop_back();
    mark[cur.x][cur.y] = false;
  }

 public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    TrieNode* root = new TrieNode();
    for (const string& word : words) {
      root->insert(word, 0);
    }
    int n = board.size(), m = board.front().size();
    vector<vector<bool>> mark(n, vector<bool>(m));
    vector<string> res;
    string path;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        findWords(n, m, board, mark, Pos(i, j), root, path, res);
      }
    }
    return res;
  } 
};
