/*
  Given a set of strings, concatenate them with '#'.
  Query a string whether it's in the concatenated string or not.
*/
#include "numeric"
#include "cassert"
#include "iostream"
#include "string"
#include "vector"

size_t search(const std::string& text, const std::string& target) {
  if (target.empty()) {
    return text.empty() || (!text.empty() && text[0] == '#') ? 
      0 : std::string::npos;
  }
  size_t low = 0, high = text.length();
  while(low < high) {
    size_t mid = (low + high) / 2;
    size_t beg = text.rfind('#', mid);
    size_t end = text.find('#', mid + 1);
    if (beg == std::string::npos) {
      assert(low == 0);
      beg = low;
    } else {
      ++ beg;
    }
    if (end == std::string::npos) {
      assert(high == text.length());
      end = text.length();
    }
    std::string now = text.substr(beg, end - beg);
    if (now == target) {
      return beg;
    } else if (now < target && beg > low) {
      low = beg;
    } else if (now > target && end < high) {
      high = end;
    } else {  // no changes, so break
      break;
    }
  }
  return std::string::npos;
}

int main() {
  std::vector<std::string> strs = 
    {"", "aa", "abcd", "abcdefg", "bb", "dd", "e", "efg"};
  std::string text = 
    std::accumulate(strs.begin() + 1, strs.end(), strs[0], 
		    [](const std::string& a, const std::string &b) {
		      return a + "#" + b;
		    });
  std::cout << text << std::endl;
  std::cout << search(text, "a") << std::endl;
  std::cout << search(text, "ee") << std::endl;
  std::cout << search(text, "e") << std::endl;
  std::cout << search(text, "defg") << std::endl;
  std::cout << search(text, "efg") << std::endl;
  std::cout << search(text, "") << std::endl;
  return 0;
}
