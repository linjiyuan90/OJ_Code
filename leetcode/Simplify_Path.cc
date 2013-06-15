class Solution {
public:
  string simplifyPath(string path) {
    VS result = split(path, "/");
    for (VS::iterator it = result.begin(); it != result.end(); ) {
      if (*it == ".") {
	it = result.erase(it);
      } else if (*it == "..") {
	it = result.erase(it);
	if (it != result.begin()) {
	  it = result.erase(it-1);
	}
      } else {
	it ++;
      }
    }
    return "/" + join("/", result);
  }

private:
  typedef vector<string> VS;

  // split s by specifying delimiters
  // empty parts will be remove
  VS split(const string &str, const string &delimiters) {
    VS result;
    for (size_t st = 0, ed = 0; ed != string::npos; ) {
      ed = str.find_first_of(delimiters, st);
      if (st < str.length() && st != ed) {
	result.push_back(str.substr(st, ed - st));
      }
      st = ed + 1;
    }
    return result;
  }

  // like python
  // ' '.join(['a', 'b', 'c'])
  string join(const string &c, const VS &strs) {
    if (strs.empty()) {
      return "";
    }
    string result = strs[0];
    for (size_t ix = 1; ix < strs.size(); ix++) {
      result += c + strs[ix];
    }
    return result;
  }
};
