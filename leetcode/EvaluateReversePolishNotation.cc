class Solution {
    
  const std::string Operators = "+-*/";
    
public:
  int evalRPN(vector<string> &tokens) {
    std::stack<int> operands;
    for (auto& s : tokens) {
      if (s.size() == 1 && Operators.find(s[0]) != std::string::npos) {
	int b = operands.top();
	operands.pop();
	int a = operands.top();
	operands.pop();
	if (s == "+") {
	  operands.push(a + b);
	} else if (s == "-") {
	  operands.push(a - b);
	} else if (s == "*") {
	  operands.push(a * b);
	} else if (s == "/") {
	  operands.push(a / b);
	} 
      } else {
	// let the exception throw
	operands.push(std::stoi(s));    
      }
    }
    return operands.top();
  }
};
