class Solution {
public:
  // O(n^2)
  // enumerate the center
  std::string longestPalindrome(std::string s) {
    std::string p = "";
    for (int ix = 0, l; ix < s.length(); ++ix) {
      for (l = 0; ix-l >= 0 && ix+l < s.length() && 
	     s[ix-l] == s[ix+l]; ++l);
      --l;
      if (2*l+1 > p.length()) {
	p = s.substr(ix-l, 2*l+1);
      }
      if (ix+1 < s.length() && s[ix] == s[ix+1]) {
	for (l = 1; ix-l+1 >= 0 && ix+l < s.length() &&
	       s[ix-l+1] == s[ix+l]; ++l);
	--l;
	if (2*l > p.length()) {
	  p = s.substr(ix-l+1, 2*l);
	}
      }
    }
    return p;
  }
};

// Manacher algorithm O(n)
// http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
// Improve by avoid recomputations of right part palindrome's length using symmetric property
class Solution {
public:
  std::string longestPalindrome(std::string s) {
    std::string t = "#";
    for (auto c : s) {
      t.push_back(c);
      t.push_back('#');
    }
    
    std::vector<int> p(t.length());
    int C = 0, R = 0;
    for (int i = 1; i < t.length(); ++i) {
      int i_mirror = C - (i-C);
      p[i] = R > i ? std::min(R - i, p[i_mirror]) : 0;
      while (t[i+1+p[i]] == t[i-1-p[i]]) {
	++ p[i];
      }
      if (i + p[i] > R) {
	R = i + p[i];
	C = i;
      }
    }
    int max_ix = std::max_element(p.begin(), p.end()) - p.begin();
    int start = (max_ix-p[max_ix]+1) / 2;
    return s.substr(start, (2*p[max_ix] + 1) / 2);
  }
};

// #a#
// #a#a#
