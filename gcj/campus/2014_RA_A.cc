#include "iostream"
#include "string"
#include "vector"
#include "map"

std::vector<std::string> Digit = {
  "zero","one","two",
  "three","four","five",
  "six", "seven","eight",
  "nine"
};

std::map<int, std::string> Rule = {
  {2, "double"},
  {3, "triple"},
  {4, "quadruple"},
  {5, "quintuple"},
  {6, "sextuple"},
  {7, "septuple"},
  {8, "octuple"},
  {9, "nonuple"},
  {10, "decuple"}
};

std::string readDigits(const std::string& digits, const std::string& format) {
  std::string ans;
  for (std::size_t s = 0, f = 0; f < format.size();) {
    std::size_t nf = format.find('-', f);
    if (nf == std::string::npos) {
      nf = format.size();
    }
    int n = std::stoi(format.substr(f, nf - f));
    f = nf + 1;
    std::size_t ns = s + n;
    for (std::size_t t = s; s < ns;) {
      t = std::min(ns, digits.find_first_not_of(digits[s], s+1));
      if (Rule.count(t - s)) {
        if (!ans.empty()) {
          ans += " ";
        }
        ans += Rule[t-s] + " " + Digit[digits[s] - '0'];
        s = t;
      } else {
        for (; s < t; ++s) {
          if (!ans.empty()) {
            ans += " ";
          }
          ans += Digit[digits[s] - '0'];
        }
      }
    }
  }
  return ans;
}

int main() {
  int T, t = 1;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::string digits, format;
    std::cin >> digits >> format;
    std::cout << readDigits(digits, format) << std::endl;
  }
  return 0;
}
