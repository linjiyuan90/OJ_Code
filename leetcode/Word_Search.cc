#include "iostream"
#include "string"
#include "vector"
#include "map"

using namespace std;

class Solution{
public:
  // whuy just brute force search will work?
  // what's complexity?
  bool exist(vector<vector<char> > &board, string word) {
    if (board.empty()) {
      return word.empty();
    }
    int n = board.size(), m = board.front().size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
	vector<int> path{i*m+j};
	if (board[i][j] == word.front() &&
	    dfs_exist(board, i, j, word.substr(1), path)) {
	  return true;
	}
      }
    }
    return false;
  }

private:
  bool dfs_exist(vector<vector<char> > &board,
		 int i,
		 int j,
		 string word,
		 vector<int> &path) {
    if (word.empty()) {
      return true;
    }
    int n = board.size(), m = board.front().size();
    int di[] = {0, 0, -1, 1};
    int dj[] = {-1, 1, 0, 0};
    for (int k = 0; k < 4; ++k) {
      int ii = i + di[k], jj = j + dj[k];
      if (is_valid(n, m, ii, jj) &&
	  board[ii][jj] == word.front() && 
	  find(path.begin(), path.end(), ii * m + jj) == path.end()) {
	path.push_back(ii * m + jj);
	if (dfs_exist(board, ii, jj, word.substr(1), path)) {
	  return true;
	}
	path.erase(--path.end());
      }
    }
    return false;
  }

  bool is_valid(int n, int m, int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
  }
};

int main() {
  Solution sol;

  std::vector<std::vector<char> > board = {
    {'A', 'B','C', 'E'}, 
    {'S', 'F', 'C', 'S'}, 
    {'A', 'D', 'E', 'E'}};
  std::cout << (sol.exist(board, "ABCCED") ? "true" : "false") << std::endl;
  std::cout << (sol.exist(board, "SEE") ? "true" : "false") << std::endl;
  std::cout << (sol.exist(board, "ABCB") ? "true" : "false") << std::endl;

  board = {
    {'A', 'B', 'C', 'D', 'E'},
    {'T', 'S', 'R', 'Q', 'F'},
    {'M', 'N', 'O', 'P', 'G'}, 
    {'L', 'K', 'J', 'I', 'H'}};
  std::cout << (sol.exist(board, "ABCDEFGHIJKLMNOPQRST") ? "true" : "false") << std::endl;

  board = {
    {'a', 'a', 'a', 'a'},
    {'a', 'a', 'a', 'a'},
    {'a', 'a', 'a', 'a'}};
  std::cout << (sol.exist(board, "aaaaaaaaaaa") ? "true" : "false") << std::endl;
}
