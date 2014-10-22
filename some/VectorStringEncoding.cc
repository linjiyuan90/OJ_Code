// encode a vector of string and decode
// use \000\x01 as separater, and transform original \000 to \000\000
// Note with empty string!

// And note that:
// \x + any number of hex digits, so \x003 is \x03!!!, Not \0003
// \ + at most 3 octal digits

#include "vector"
#include "string"
#include "algorithm"
#include "cassert"
#include "iostream"

std::string encode(const std::vector<std::string>& strs) {
  std::string encode;
  for (auto& str : strs) {
    for (auto& ch : str) {
      if (ch == 0) {
        encode.push_back(0);
      }
      encode.push_back(ch);
    }
    encode.push_back(0);
    encode.push_back(1);
  }
  return encode;
}

std::vector<std::string> decode(const std::string& str) {
  std::vector<std::string> strs;
  for (int i = 0, n = str.size(); i + 1 < n; ++i) {
    if (strs.empty()) {
      strs.push_back("");
    }
    if (str[i] == 0 && str[i+1] == 1) {
      if (i + 2 < n) {
        strs.push_back("");
      }
      ++i;
      continue;
    } else if (str[i] == 0 && str[i+1] == 0) {
      ++i;
    }
    strs.back().push_back(str[i]);
  }
  return strs;
}

void printBytes(const std::string& str) {
  for (auto& ch : str) {
    std::cout << (int)ch << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<std::string> strs = {
    {"12\0003\x01", 5},
    {"", 0},
    {"456\000\x01", 5},
    {"789", 3}, 
    {"\000\x01", 2}
  };
  auto strs2 = decode(encode(strs));
  assert(strs == strs2);
  for (int i = 0, n = strs.size(); i < n; ++i) {
    if (strs[i] != strs2[i]) {
      printBytes(strs[i]);
      printBytes(strs2[i]);
    }
  }
  return 0;
}
