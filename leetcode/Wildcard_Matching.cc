#include "iostream"
#include "vector"
#include "cstring"
#include "string"

using namespace std;

class Solution {
public:

  typedef vector<string> VS;
  
  bool isMatch(const char *s, const char *p) {
    string ps = compress_star(p);
    p = ps.c_str();
    int n = strlen(s), m = strlen(p);
    int si = 0, sj = n - 1;
    int pi = 0, pj = m - 1;
    // head
    for (;si <= sj && pi <= pj && p[pi] != '*'; si++, pi++) {
      if (s[si] != p[pi] && p[pi] != '?') {
	return false;
      }
    }
    // tail
    for (;si <= sj && pi <= pj && p[pj] != '*'; sj--, pj--) {
      if (s[sj] != p[pj] && p[pj] != '?') {
	return false;
      }
    }
    if (pi > pj && si <= sj) {
      return false;
    }
    // make p looks like *p1*p2..pk*
    for (string word : split(string(p+pi, pj-pi+1), "*")) {
      bool is_match = false;
      for (int n = word.length(); sj - si + 1 >= n; si++) {
	if (match(string(s+si, n), word)) {
	  si += n;
	  is_match = true;
	  break;
	}
      }
      if (!is_match) {
	return false;
      }
    }
    return true;
  }

  bool match(const string &a, const string &b) {
    for (size_t ix = 0; ix < a.length(); ix++) {
      if (a[ix] != b[ix] && b[ix] != '?') {
	return false;
      }
    }
    return true;
  }
  
  string compress_star(const char *p) {
    string ps;
    for (; *p; p++) {
      if (*p == '*' && !ps.empty() && ps.back() == '*') {
	continue;
      }
      ps += *p;
    }
    return ps;
  }
  
  VS split(const std::string &str, const std::string &delimiters) {
    VS result;
    for (size_t st = 0, ed = 0; ed != std::string::npos; ) {
      ed = str.find_first_of(delimiters, st);
      if (st < str.length() && st != ed) {
	result.push_back(str.substr(st, ed - st));
      }
      st = ed + 1;
    }
    return result;
  }
};

int main() {
  Solution sl;
  char s[1000] = "mississippi", p[1000] = "m*iss*";
  //cin >> s >> p;
  cout << sl.isMatch(s, p);
}
