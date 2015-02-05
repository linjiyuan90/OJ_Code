class Solution {
  std::string formLine(std::vector<std::string>& words, int sum, int L) {
    // form a line
    std::string line(L, ' ');
    std::copy(words.front().begin(), words.front().end(), line.begin());
    if (words.size() > 1) {
      std::copy(words.back().rbegin(), words.back().rend(), line.rbegin());
      int spaces = (L - sum) / (words.size() - 1);
      int left = L - sum - spaces * (words.size() - 1);
      std::string::iterator p = line.begin() + words.front().size();
      for (auto it = words.begin() + 1; it != words.end() - 1; ++it) {
        p += spaces;
        if (left > 0) {
          ++ p;
          -- left;
        }
        std::copy(it->begin(), it->end(), p);
        p += it->size();
      }
    }   
    return line;
  }
    
public:
  vector<string> fullJustify(vector<string>& words, int L) {
    std::vector<std::string> ans;
    std::vector<std::string> line;
    int lineSum = 0;
    for (auto& w : words) {
      if (lineSum + line.size() + w.size() <= L) {
        line.push_back(w);
        lineSum += w.size();
      } else {
        ans.push_back(formLine(line, lineSum, L));
        line.clear();
        line.push_back(w);
        lineSum = w.size();
      }
    }
    if (!line.empty()) {  // last line is different!
      std::string lineStr = std::accumulate(line.begin() + 1, line.end(), line.front(), 
                                            [](const std::string& a, const std::string& b) {
                                              return a + " "  + b;
                                            });
      lineStr.resize(L, ' ');
      ans.push_back(lineStr);
    }
    return ans;
  }
};
