class Solution {
public:
  string longestCommonPrefix(vector<string> &strs) {
    if (strs.empty()) {
      return "";
    }
    string prefix = strs.front();
    for (size_t i = 1; i < strs.size(); ++i) {
      auto it = mismatch(prefix.begin(),
                         prefix.end(),
                         strs[i].begin()).first;
      prefix = prefix.substr(0, it - prefix.begin());
    }
    return prefix;
  }
};
