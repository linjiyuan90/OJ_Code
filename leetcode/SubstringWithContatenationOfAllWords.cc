#include "iostream"
#include "vector"
#include "algorithm"
#include "string"
#include "unordered_map"

class Solution {
public:
  // note words in L are of same length
  std::vector<int> findSubstring(std::string S, std::vector<std::string> &L) {
    std::vector<int> ans;
    if (L.empty()) {
      return ans;
    }
    std::unordered_map<std::string, int> word_cnt;
    for (auto &e : L) {
      ++word_cnt[e];
    }
    int len = L[0].length();
    int sum_len = len * L.size();
    // [0, len)
    for (size_t start = 0; start < len; ++start) {
      std::unordered_map<std::string, int> s_word_cnt;
      int matches = 0;
      for (size_t ix = start; ix + len <= S.length(); ix += len) {
	// ix - sum_len will be negative overflow
	if (ix >= start + sum_len) {
	  std::string w = S.substr(ix - sum_len, len);
	  if (word_cnt.count(w) && --s_word_cnt[w] < word_cnt[w]) {
	    --matches;
	  }
	}
	std::string w = S.substr(ix, len);
	if (word_cnt.count(w) && ++s_word_cnt[w] <= word_cnt[w]) {
	    ++ matches;
	}
	if (matches == L.size()) {
	  ans.push_back(ix - sum_len + len);
	}
      }
    }
    // no need to sort
    // std::sort(ans.begin(), ans.end());
    return ans;
  }
};

int main() {
  Solution s;
  // std::string S(60000, 'a');
  std::string S = "lingmindraboofooowingdingbarrwingmonkeypoundcake";  // "barfoothefoobarman";
  // std::vector<std::string> L(300, "a");
  auto L = std::vector<std::string>{"fooo","barr","wing","ding","wing"}; // {"foo", "bar"};
  for (auto e : s.findSubstring(S, L)) {
      std::cout << e << " ";
    }
  return 0;
}
