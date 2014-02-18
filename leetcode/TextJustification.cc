class Solution {
public:
  std::vector<std::string> fullJustify(std::vector<std::string> &words, int L) {
    std::vector<std::string> ans;
    std::vector<std::string> line;
    int len = 0;
    for (auto w : words) {
      if (!line.empty() && len + line.size() + w.length() > L) {
	if (line.size() == 1) {
	  line[0].resize(L, ' ');
	  ans.push_back(line[0]);
	} else {
	  int blank = L - len;
	  int gap = blank / (line.size() - 1);
	  int left = blank % (line.size() - 1);
	  std::string s = line.front();
	  for (int i = 1; i < line.size(); ++i) {
	    if (left > 0) {
	      s += " ";
	      -- left;
	    }
	    s += std::string(gap, ' ') + line[i];
	  }
	  ans.push_back(s);
	}
	len = 0;
	line.clear();
      }
      line.push_back(w);
      len += w.length();
    }
    if (!line.empty()) {
      std::string s = line.front();
      for (int i = 1; i < line.size(); ++i) {
	s += " " + line[i];
      }
      s.resize(L, ' ');
      ans.push_back(s);
    }
    return ans;
  }
};
