class Solution {
public:
  std::vector<std::string> anagrams(std::vector<std::string> &strs) {
    std::unordered_map<std::string, int> hash_map;
    for (auto e : strs) {
      std::sort(e.begin(), e.end());
      ++hash_map[e];
    }
    std::vector<std::string> ans;
    for (auto &e : strs) {
      std::string s = e;
      std::sort(s.begin(), s.end());
      if (hash_map[s] > 1) {
	ans.push_back(e);
      }
    }
    return ans;
  }
};
