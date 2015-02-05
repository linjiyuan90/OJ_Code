class Solution {
public:
  // my damn code is to use dfs
  // in fact, just loop and erase
  int longestConsecutive(vector<int> &num) {
    std::unordered_map<int, int> hash;
    for (int &a : num) {
      hash[a] = 1;
    }
    int ans = 0;
    for (int &a : num) {
      if (!hash.count(a)) {
	continue;
      }
      for (int b = a + 1; hash.count(b); ++b) {
	hash[a] += hash[b];
	hash.erase(b);
      }
      ans = std::max(ans, hash[a]);
    }
    return ans;
  }
};
