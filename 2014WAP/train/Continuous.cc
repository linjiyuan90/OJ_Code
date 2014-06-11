#include "iostream"
#include "string"
#include "vector"


std::string continuous(std::string seq) {
  std::string ans, last;
  char last_ch = ' ';
  for (char &ch : seq) {
    if (ch == last_ch) {
      last += ch;
    } else {
      last = ch;
    }
    if (ans.size() < last.size()) {
      ans = last;
    }
    last_ch = ch;
  }
  return ans;
}

std::string intersect(std::string seq) {
  std::string ans, last;
  char last_ch = ' ';
  for (char &ch : seq) {
    if (last_ch != ' ' && ch != last_ch) {
      last += ch;
    } else {
      last = ch;
    }
    if (ans.size() < last.size()) {
      ans = last;
    }
    last_ch = ch;
  }
  return ans;
}

int main() {
  for (std::string seq; std::cin >> seq;) {
    std::cout << continuous(seq) << std::endl;
    std::cout << intersect(seq) << std::endl;
  }
}
