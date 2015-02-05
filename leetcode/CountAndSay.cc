
class Solution {    
public:
  std::string countAndSay(int n) {
    std::string now = "1";
    for (int i = 2; i <= n; ++i) {
      std::string next;
      for (std::size_t p = 0; p != now.length(); ) {
	std::size_t q = now.find_first_not_of(now[p], p);
	// note, otherwise q - p will be really big!
	if (q == std::string::npos) {
	  q = now.length();
	}
	next += std::to_string(q - p) + now[p];
	p = q;
      }
      now = next;
    }
    return now;
  }
};
