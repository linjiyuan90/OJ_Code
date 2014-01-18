#include "iostream"
#include "vector"
#include "cstring"
#include "string"

class Solution {
public:

  typedef std::vector<std::string> VS;

  // add '|' to the front and end of s and p to make later handle easier
  // split p by '*' to get a list of segments which consist only alpha, '|', and '?'
  // 
  // The match phase is for each segments in p, find the first match in s
  // (No need to backstrap)
  bool isMatch(const char *s, const char *p) {
    std::string ss = "|" + std::string(s) + "|";
    std::string pp = "|" + std::string(p) + "|";
    
    VS segments = split(pp, '*');

    size_t now = 0;
    for (auto seg : segments) {
      now = find(ss, seg, now); 
      if (now == std::string::npos) {
	return false;
      }
      now += seg.length();
    }
    return true;
  }
  
  VS split(const std::string &str, const char &sep) {
    VS result;
    for (auto c : str) {
      if (c == sep) {
	if (result.back() != "") {
	  result.push_back("");
	}
      } else {
	if (result.empty()) {
	  result.push_back(std::string(1, c));
	} else {
	  result.back() = result.back() + c;
	}
      }
    }
    return result;
  }

  // match with wildcard '?'
  // how to accelerate this?
  size_t find(const std::string &str,
	      const std::string &sub_str,
	      size_t start) {
    for (size_t ix = start; ix + sub_str.length() <= str.length(); ++ix) {
      size_t i = 0;
      while (i < sub_str.length() && 
	     (str[ix + i] == sub_str[i] || sub_str[i] == '?')) {
	++ i;
      }
      if (i == sub_str.length()) {
	return ix;
      }
    }
    return std::string::npos;
  }
};

int main() {
  Solution sl;
  // char s[1000] = "mississippi", p[1000] = "m*iss*?";
  char s[1000] = "aa", p[1000] = "a";
  //cin >> s >> p;
  std::cout << sl.isMatch(s, p) << std::endl;
}
