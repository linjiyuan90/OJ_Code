#include "iostream"
#include "string"
#include "map"
#include "stack"

std::map<char, char> LEFT = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
std::map<char, char> RIGHT = {{')', '('}, {']', '['}, {'}', '{'}};

std::pair<bool, std::stack<char>> is_valid(const std::string &seq) {
  std::stack<char> s;
  for (const char &c : seq) {
    if (LEFT.count(c)) {
      s.push(c);
    }
    if (RIGHT.count(c)) {
      if (!s.empty() && s.top() == RIGHT[c]) {
	s.pop();
      } else {  // impossible to match
	return std::make_pair(false, s);
      }
    }
  }
  return std::make_pair(true, s);
}

int main() {
  for(std::string seq; std::cin >> seq; ) {
    auto res = is_valid(seq);
    if (res.first) {
      auto &s = res.second;
      std::string addl;
      while(!s.empty()) {
	addl += LEFT[s.top()];
	s.pop();
      }
      std::cout << seq << addl << std::endl;;
    } else {
      std::cout << "impossible!" << std::endl;
    }
  }
  return 0;
}
