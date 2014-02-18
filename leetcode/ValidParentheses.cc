class Solution {
public:
  bool isValid(std::string s) {
    std::stack<char> S;
    for (auto c : s) {
      if (pairs.count(c)) {
	S.push(c);
      } else {
	if (S.empty() || pairs[S.top()] != c) {
	  return false;
	}
	S.pop();
      }
    }
    return S.empty();
  }

private:
  std::map<char, char> pairs = {
    {'(', ')'}, {'{', '}'}, {'[', ']'}
  };
};
