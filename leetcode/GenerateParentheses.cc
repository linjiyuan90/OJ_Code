class Solution {
public:
  // just enumerate the head structure
  std::vector<std::string> generateParenthesis(int n) {
    if (n == 0) {
      return std::vector<std::string>{""};
    }
    std::vector<std::string> ans;
    for (int i = 0; i <= n - 1; ++i) {
      for (auto left : generateParenthesis(i)) {
	for (auto right : generateParenthesis(n - 1 - i)) {
	  ans.push_back("(" + left + ")" + right);
	}
      }
    }
    return ans;
  }
};
