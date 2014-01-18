#include "unordered_set"
#include "unordered_map"
#include "vector"
#include "string"
#include "iostream"
#include "queue"

class Solution {
public:
  int ladderLength(std::string start,
		   std::string end,
		   std::unordered_set<std::string> &dict) {
    std::unordered_map<std::string, std::vector<std::string>> candidates;
    std::unordered_map<std::string, int> dist;
    dict.insert(end);
    for (auto it = dict.begin(); it != dict.end(); ++ it) {
      std::string s = *it;
      for (size_t ix = 0; ix < s.length(); ++ix) {
	candidates[pattern(s, ix)].push_back(*it);
      }
    }
    std::queue<std::pair<std::string, int>> q;
    q.push(std::make_pair(start, 1));
    dist[start] = 0;
    while (!q.empty()) {
      auto s = q.front().first;
      auto d = q.front().second;
      q.pop();
      for (size_t ix = 0; ix < s.length(); ++ix) {
	auto t = pattern(s, ix);
	auto &candidate = candidates[t];
	for (auto it = candidate.begin(); it != candidate.end(); ++it) {
	  if (*it == end) {
	    return d + 1;
	  }
	  if (!dist.count(*it)) {
	    dist[*it] = d + 1;
	    q.push(std::make_pair(*it, d + 1));
	  }
	}
      }
    }
    return 0;
  }

private:
  std::string pattern(const std::string &s, int ix) {
    return s.substr(0, ix) + '*' + s.substr(ix+1);
  }
};

int main() {
  Solution sol;
  std::unordered_set<std::string> dict {"hot", "dot", "dog", "lot", "log"};
  std::cout << sol.ladderLength("hit","cog", dict) << std::endl;
}
