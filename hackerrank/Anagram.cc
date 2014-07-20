// Two strings are Anagram if they are same after sorted
// That's, one string is same as the other after some permutation.

// The question is given two strings, how many chars need to be replaced to make
// them anagram.

#include "iostream"
#include "string"
#include "map"

int min_diff(const std::string& str) {
  std::map<char, int> left, right;
  for(int i = 0, j = str.length() - 1; i < j; ++i, --j) {
    ++ left[str[i]];
    ++ right[str[j]];
  }
  int res = 0;
  for (char ch = 'a'; ch <= 'z'; ++ch) {
    res += ::abs(left[ch] - right[ch]);
  }
  return res/2;  // need to divide 2!
}

int main() {
  int T;
  for (std::cin >> T; T--; ) {
    std::string str;
    std::cin >> str;
    if (str.length() % 2 != 0) {
      std::cout << -1 << std::endl;
    } else {
      std::cout << min_diff(str) << std::endl;
    }
  }
}
