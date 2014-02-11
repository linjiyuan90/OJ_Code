class Solution {
public:
  // Using a hash to achieve O(n)?
  int longestConsecutive(std::vector<int> &num) {
    std::unordered_map<int, int> hash;
    for (auto e : num) {
      hash[e] = 1;
    }
    int ans = 0;
    for (auto e : num) {
      if (!hash.count(e)) {
	continue;
      }
      for (int d = e+1; hash.count(d); ++d) {
	hash[e] += hash[d];
	hash.erase(d);
      }
      ans = std::max(ans, hash[e]);
    }
    return ans;
  }
};
