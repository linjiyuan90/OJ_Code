#include "iostream"
#include "string"
#include "vector"

class Solution {
public:
  std::vector<std::vector<std::string>> partition(std::string s) {
    // recursive solution 
    // enumerate the palindrome head of s, combine the head with the 
    // tail partition
    // "abaab"
    // {"a", partition("baab")}
    // {"aba", partition("ab")}
    
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> path;
    partition(s, res, path);
    return res;
  }
  
private:
  void partition(std::string s,
		 std::vector<std::vector<std::string>> &res,
		 std::vector<std::string> &path) {
    if (s.empty()) {
      res.push_back(path);
      return;
    }
    for (size_t len = 1; len <= s.length(); ++ len) {
      auto prefix = s.substr(0, len);
      if (is_palindrome(prefix)) {
	path.push_back(prefix);
	partition(s.substr(len), res, path);
	path.erase(--path.end());
      }
    }
  }
  
  bool is_palindrome(const std::string &s) {
    auto r = s;
    std::reverse(r.begin(), r.end());
    return r == s;
  }
};

int main() {
  Solution sol;
  auto ans = sol.partition("aab");
  for (auto it = ans.begin(); it != ans.end(); ++ it) {
    for (auto jt = it->begin(); jt != it->end(); ++ jt) {
      std::cout << *jt << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
