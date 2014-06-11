#include "iostream"
#include "vector"
#include "string"

std::string max_repeated_substring(const std::string &str) {
  std::string ans = "";
  int max_times = 0;
  int n = str.size();
  for (int L = n; L > 0; --L) {
    // store continuous same substring
    for (int start = 0, i; start < L; ++start) {
      std::vector<std::string> vt;
      for (i = start; i + L <= n; i += L) {
	if (vt.empty() || vt.back() != str.substr(i, L)) {
	  if (max_times < vt.size()) {
	    max_times = vt.size();
	    ans = str.substr(i - max_times * L, max_times * L);
	  }
	  vt.clear();
	}
	vt.push_back(str.substr(i, L));
      }
      if (max_times < vt.size()) {
	max_times = vt.size();
	ans = str.substr(i - max_times * L, max_times * L);
      }
    }
  }
  return ans;
}

int main() {
  for (std::string str; std::cin >> str; ) {
    std::cout << max_repeated_substr(str) << std::endl;
  }
  return 0;
}
