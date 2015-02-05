class Solution {
public:
  int longestValidParentheses(string s) {
    // one stack to record position of '('
    // another stack to record the valid parentheses position
    std::stack<int> left_parenthese;
    std::stack<std::pair<int, int>> parentheses;
    int ans = 0;
    for (std::size_t i = 0, n = s.size(); i < n; ++i) {
      if (s[i] == ')') {
	// valid parenthese
	if (!left_parenthese.empty()) {
	  std::pair<int, int> now{left_parenthese.top(), i};
	  left_parenthese.pop();
	  // merge with previous valid parentheses
	  // ((....))
	  // ^      ^
	  // left   i
	  // or
	  // (..)(....)
	  //     ^....^
	  //     left i
	  if (!parentheses.empty()) {
	    auto last = parentheses.top();
	    if (now.first == last.first - 1 && last.second + 1 == now.second) {
	      parentheses.pop();
	    }
	  }
	  if (!parentheses.empty()) {
	    auto last = parentheses.top();
	    if (now.first == last.second + 1) {
	      now.first = last.first;
	      parentheses.pop();
	    }
	  }
	  ans = std::max(ans, now.second - now.first + 1);
	  parentheses.push(now);
	}
      } else {
	left_parenthese.push(i);
      }
    }
    return ans;
  }
};

// ()(())

