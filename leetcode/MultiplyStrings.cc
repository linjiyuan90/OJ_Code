class Solution {
public:
  std::string multiply(std::string num1, std::string num2) {
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    
    // using std::vector<int> is more convenient
    std::vector<int> ans(num1.size() + num2.size());
    for (int i = 0; i < num1.size(); ++i) {
      int c = 0;
      for (int j = 0; j < num2.size(); ++j) {
	c += (num1[i] - '0') * (num2[j] - '0') + ans[i+j];
	ans[i+j] = c % 10;
	c /= 10;
      }
      for (int j = num2.size(); c > 0; ++j) {
	c += ans[i+j];
	ans[i+j] = c % 10;
	c /= 10;
      }
    }
    while (ans.size() > 1 && ans.back() == 0) {
      ans.pop_back();
    }
    std::string res;
    for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
      res.push_back(*it + '0');
    }
    return res;
  }
};
