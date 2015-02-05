class Solution {
public:
  string multiply(string num1, string num2) {
    int n = num1.size(), m = num2.size();
    if (n == 0 || m == 0) {
      throw std::invalid_argument("Multiply empty string");
    }
    std::vector<int> ans(n + m);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
	ans[i+j] += (num1[n-1-i] - '0') * (num2[m-1-j] - '0');
	if (ans[i+j] >= 10) {
	  ans[i+j+1] += ans[i+j] / 10;
	}
	ans[i+j] %= 10;
      }
    }
    while(ans.size() > 1 && ans.back() == 0) {
      ans.pop_back();
    }
    std::string ans_str;
    for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
      ans_str += std::to_string(*it);
    }
    return ans_str;
  }
};
