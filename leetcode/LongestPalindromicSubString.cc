
class Solution {
public:
  // Manachor algorithm O(n)
  // http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
  // Improve by avoid recomputations of right part palindrome's length using symmetric property
  std::string longestPalindrome(std::string s) {
    int n = s.length();
    std::string str(2*n+1, '#');
    for (int i = 0; i < n; ++i) {
      str[2*i+1] = s[i];
    }
    int m = str.length();
    // part[i]:
    // longest length that str[i-part[i]...i+part[i]] are symmetric
    // centered at i
    std::vector<int> part(m);
    for (int i = 0, C = 0, R = 0; i < m; ++i) {
      // avoid recomputations using symmetric property
      int ii = C - (i-C);
      part[i] = R > i ? std::min(R-i, part[ii]) : 0;
      while(i+part[i]+1 < m
	    && i-part[i]-1 >= 0 
	    && str[i+part[i]+1] == str[i-part[i]-1]) {
	  ++part[i];
      }
      if (i+part[i] > R) {
	R = i + part[i];
	C = i;
      }
    }
    // #a#
    // #a#a#
    int max_ix = std::max_element(part.begin(), part.end()) - part.begin();
    int off = (max_ix - part[max_ix] + 1) / 2;
    int len = (2*part[max_ix] + 1) / 2;
    return s.substr(off, len);
  }

  // O(n^2) solution is to enumerate centor then expand, like manachor by repcomputing ...
};
