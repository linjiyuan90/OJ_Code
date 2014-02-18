class Solution {
public:
  std::vector<std::string> letterCombinations(std::string digits) {
    std::vector<std::string> ans;
    std::string cur;
    dfs(ans, digits, 0, cur);
    return ans;
  }

private:
  std::vector<std::string> numbers = {
    "abc", "def", "ghi", "jkl",
    "mno", "pqrs", "tuv", "wxyz"
  };
  
  void dfs(std::vector<std::string> &ans, 
	   std::string &digits, 
	   int ix,
	   std::string &cur) {
    if (ix == digits.size()) {
      ans.push_back(cur);
      return;
    }
    for (auto ch : numbers[digits[ix] - '2']) {
      cur.push_back(ch);
      dfs(ans, digits, ix+1, cur);
      cur.pop_back();
    }
  }
};
