#include "iostream"
#include "string"
#include "vector"

// return (offset, len)
// if offset = -1, that means there is no repeated substring
std::pair<int, int> longest_repeated_substring(const std::string &str) {
  int n = str.length();
  auto num_char = std::vector<int>(n, 0);
  int off = -1, max_len = 0;
  // enumerate period
  for (int period = n/2; period >= 1; --period) {
    num_char.assign(n, 0);
    // num_char[i] means 
    // str[i-num_char[i]+1..i] == str[j-num_char[i]+1..j] 
    // where j = i - period
    // num_period[i] means 
    // str[j+1..j+period] == str[j+period+1..j+2*period] == .. == str[i-period+1..i]
    // where j = i - num_period[i]*period
    for (int ix = 0; ix < n; ++ix) {
      if (ix >= period) {
	if (str[ix - period] == str[ix]) {
	  num_char[ix] = num_char[ix-1] + 1;
	}
      }
      int num_period = num_char[ix] < period ? 0 : num_char[ix] / period + 1;
      if (num_period*period > max_len) {
	max_len = num_period*period;
	off = ix - max_len + 1;
      }
    }
  }
  return std::make_pair(off, max_len);
}

int main() {
  for (auto s: std::vector<std::string>{
      "abcd", "abcdabcd", "ababa", "xxyyxx", "axxyxxy",
	"abcdabcdab", "aabbbbaa"
	}) {
    auto pair = longest_repeated_substring(s);
    int off = pair.first, len = pair.second;
    if (off == -1) {
      std::cout << "There is no repeated substring in " << s << std::endl;
    } else {
      std::cout << "The longest repeated substring of " << s << " is " 
		<< s.substr(off, len) << std::endl;
    }
  }
  return 0;
}
