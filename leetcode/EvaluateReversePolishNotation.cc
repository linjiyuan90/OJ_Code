#include "iostream"
#include "string"
#include "vector"
#include "stack"

class Solution {
public:
  int evalRPN(std::vector<std::string> &tokens) {
    auto getAB = [](std::stack<int> &eles) {
      int b = eles.top();
      eles.pop();
      int a = eles.top();
      eles.pop();
      return std::pair<int, int> (a, b);
    };
    std::stack<int> eles;
    for (auto &e : tokens) {
      if (e == "+") {
	auto ab = getAB(eles);
	eles.push(ab.first + ab.second);
      } else if (e == "-") {
	auto ab = getAB(eles);
	eles.push(ab.first - ab.second);
      }	else if (e == "*") {
	auto ab = getAB(eles);
	eles.push(ab.first * ab.second);
      } else if (e == "/") {
	auto ab = getAB(eles);
	eles.push(ab.first / ab.second);
      } else {
	eles.push(::atoi(e.c_str()));
      }
    }
    return eles.top();
  }
};
