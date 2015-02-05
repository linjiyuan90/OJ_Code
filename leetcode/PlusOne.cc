class Solution {
public:
  vector<int> plusOne(vector<int> &digits) {
    std::reverse(digits.begin(), digits.end());
    int c = 1;
    for (int i = 0, n = digits.size(); i < n && c > 0; ++i) {
      c += digits[i];
      digits[i] = c % 10;
      c = c / 10;
    }
    if (c > 0) {
      digits.push_back(c);
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
  }
};
