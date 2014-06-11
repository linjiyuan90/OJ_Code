#include "iostream"
#include "string"

int main() {
  for (std::string num; std::cin >> num; ) {
    std::string ans, last;
    for (int i = 0, j = 0; i < num.size(); ++i) {
      if (i == 0 || num[i-1] >= num[i]) {  // restart
	last = "";
	j = i;
      }
      last += num[i];
      if (last.size() > ans.size() || 
	  (last.size() == ans.size() && last > ans)) {
	ans = last;
      }
    }
    std::cout << ans << std::endl;
  }
  return 0;
}
