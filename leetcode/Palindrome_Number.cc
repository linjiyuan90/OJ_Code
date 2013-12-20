#include "iostream"

class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0) {
      return false;
    }
    if (x < 10) {
      return true;
    }
    // deal with tailing zeros, like 131000
    if (x % 10 == 0) {
      return false;
    }
    // Is this an extra space ?
    for (int y = 0; ; y = y*10 + x % 10, x /= 10) {
      if (x == y || x / 10 == y) {
	return true;
      }
      if (x == 0) {
	return false;
      }
    }
  }
};

int main() {
  Solution sol;
  std::cout << sol.isPalindrome(0) << std::endl;
  std::cout << sol.isPalindrome(1) << std::endl;
  std::cout << sol.isPalindrome(10) << std::endl;
  std::cout << sol.isPalindrome(1221) << std::endl;
  std::cout << sol.isPalindrome(131000) << std::endl;
  std::cout << sol.isPalindrome(2111111112) << std::endl;
  return 0;
}
