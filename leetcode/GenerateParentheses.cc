class Solution {
  // enumerate the first pair of parenthese
  std::vector<string> generateParenthesisImpl(int n) {
    std::vector<std::string> ans;
    if (n == 0) {
      ans.push_back("");
    } else {
      for (int inside = 0; inside < n; ++inside) {
        auto left = generateParenthesisImpl(inside);
        auto right = generateParenthesisImpl(n - inside - 1);
        for (auto& l : left) {
          for (auto& r : right) {
            ans.push_back("(" + l + ")" + r);
          }
        }
      }
    }
    return ans;
  }
public:
  vector<string> generateParenthesis(int n) {
    return generateParenthesisImpl(n);
  }
};
