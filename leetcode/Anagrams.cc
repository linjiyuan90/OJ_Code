class Solution {
public:
  vector<string> anagrams(vector<string> &strs) {
    std::unordered_map<std::string, int> cnt;
    for (auto str : strs) {
      std::sort(str.begin(), str.end());
      ++ cnt[str];
    }
    std::vector<std::string> res;
    for (auto &e : strs) {
      auto s = e;
      std::sort(s.begin(), s.end());
      if (cnt[s] > 1) {
	res.push_back(e);
      }
    }
    return res;
  }
};
