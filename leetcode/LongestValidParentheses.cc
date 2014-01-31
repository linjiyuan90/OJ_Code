#include "iostream"
#include "stack"
#include "string"

class Solution {
public:
  int longestValidParentheses(std::string s) {
    std::stack<int> left_parenthese;
    std::stack<std::pair<int, int>> valid_pairs;
    int ans = 0;
    for (size_t ix = 0; ix < s.length(); ++ix) {
      if (s[ix] == '(') {
	left_parenthese.push(ix);
      } else if (!left_parenthese.empty()) {
	int l = left_parenthese.top();
	left_parenthese.pop();
	std::pair<int, int> new_valid(ix, ix);
	if (l == ix - 1) {
	  new_valid = std::make_pair(l, ix);
	}
	if (!valid_pairs.empty() && valid_pairs.top().first == l + 1) {
	  new_valid = std::make_pair(l, ix);
	  valid_pairs.pop(); // note
	}
	while (!valid_pairs.empty() &&
	       valid_pairs.top().second == new_valid.first - 1) {
	  new_valid.first = valid_pairs.top().first;
	  valid_pairs.pop();
	}
	if (new_valid.first < ix) {
	  valid_pairs.push(new_valid);
	  ans = std::max(ans, new_valid.second - new_valid.first + 1);
	}
      }
    }
    return ans;
  }
};

// (()((())))
int main() {
  Solution sol;
  std::cout << sol.longestValidParentheses("(()((((((()()(") << std::endl;
  return 0;
}
