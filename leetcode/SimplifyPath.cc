class Solution {
public:
  string simplifyPath(string path) {
    std::vector<std::string> parts;
    for (std::size_t i = 0, n = path.size(); i <= n; ++i) {
      if (i == n || path[i] == '/') {
        if (!parts.empty()) {
          if (parts.back() == ".") {
            parts.pop_back();
          } else if (parts.back() == "..") {
            parts.pop_back();
            if (!parts.empty()) {
              parts.pop_back();
            }
          }
        }
        if (parts.empty() || !parts.back().empty()) {
          parts.push_back("");
        }
      } else {
        parts.back() += path[i];
      }
    }
    if (!parts.empty() && parts.back().empty()) {
      parts.pop_back();
    }
    if (parts.empty()) {
      return "/";
    }
    return std::accumulate(parts.begin(), parts.end(), 
                           std::string(), 
                           [](const std::string&a, const std::string& b) {
                             return a + "/" + b;
                           });
  }
};

// note "///", "/..", "/."
