class Solution {
public:
  std::vector<int> plusOne(std::vector<int> &digits) {
    std::reverse(digits.begin(), digits.end());
    int c = 1;
    for (auto &d : digits) {
      if (c == 0) {
	break;
      }
      d = d + c;
      c = d / 10;
      d = d % 10;
    }
    if (c != 0) {
      digits.push_back(1);
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
  }
};
