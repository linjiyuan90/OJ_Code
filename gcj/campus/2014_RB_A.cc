#include "iostream"
#include "algorithm"
#include "numeric"
#include "cmath"
#include "vector"

bool is_valid(std::vector<std::vector<int>> board) {
  int n = board.size();
  for (int i = 0; i < n; ++i) {
    auto vertical_nums = std::vector<int>(n, 0);
    auto horizontal_nums = std::vector<int>(n, 0);
    for (int j = 0; j < n; ++j) {
      if (1 <= board[j][i] && board[j][i] <= n) {
	vertical_nums[board[j][i] - 1] = 1;
      }
      if (1 <= board[i][j] && board[i][j] <= n) {
	horizontal_nums[board[i][j] - 1] = 1;
      }
    }
    if (std::accumulate(vertical_nums.begin(), vertical_nums.end(), 0) != n || 
	std::accumulate(horizontal_nums.begin(), horizontal_nums.end(), 0) != n) {
      return false;
    }
  }
  // subboard check
  int sn = ::sqrt(n);
  for (int i = 0; i < sn; ++i) {
    for (int j = 0; j < sn; ++j) {
      auto nums = std::vector<int>(n, 0);
      int x = i*sn, y = j*sn;
      for (int k = 0; k < n; ++k) {
	int xx = x + k / sn, yy = y + k % sn;
	if (1 <= board[xx][yy] && board[xx][yy] <= n) {
	  nums[board[xx][yy] - 1] = 1;
	}
      }
      if (std::accumulate(nums.begin(), nums.end(), 0) != n) {
	return false;
      }
    }
  }
  return true;
}

std::vector<std::vector<int>> read_board(int n) {
  int n2 = n * n;
  auto board = std::vector<std::vector<int>> (n2, std::vector<int>(n2));
  for (int i = 0; i < n2; ++i) {
    for (int j = 0; j < n2; ++j) {
      std::cin >> board[i][j];
    }
  }
  return std::move(board);
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 1, n; t <= T; ++t) {
    std::cin >> n;
    std::cout << "Case #" << t 
	      << ": " << (is_valid(read_board(n)) ? "Yes" : "No") 
	      << std::endl;
  }
  return 0;
}
