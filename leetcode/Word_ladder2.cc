#include "iostream"
#include "unordered_map"
#include "unordered_set"
#include "vector"
#include "string"
#include "queue"

// 1840 ms
class Solution {
public:
  std::vector<std::vector<std::string>> 
  findLadders(std::string start,
	      std::string end,
	      std::unordered_set<std::string> &dict) {
    if (start == end) {
      return std::vector<std::vector<std::string>> {
	std::vector<std::string>{start, end}
      };
    }
    
    // generate candidates
    dict.insert(end);
    generate_candidates(dict);
    
    // bfs to calculate dist
    bfs(start, end);

    if (!dist.count(end)) {
      return std::vector<std::vector<std::string>>();
    }

    // dfs to generate combintion
    std::vector<std::vector<std::string>> res;
    std::vector<std::string> path;
    dfs(start, end, res, path);
    return res;
  }

private:
  std::string pattern(const std::string &s, const int &ix) {
    return s.substr(0, ix) + '*' + s.substr(ix+1);
  }

  void generate_candidates(std::unordered_set<std::string> &dict) {
    for (auto it = dict.begin(); it != dict.end(); ++it) {
      auto &s = *it;
      for (size_t ix = 0; ix < s.length(); ++ix) {
	candidates[pattern(s, ix)].push_back(s);
      }
    }
  }

  void bfs(const std::string &start, const std::string &end) {
    std::queue<std::pair<std::string, int>> q;
    q.push(std::make_pair(start, 0));
    dist[start] = 0;
    while(!q.empty()) {
      auto s = q.front().first;
      auto d = q.front().second;
      q.pop();
      if (s == end) {
	break;
      }
      // neighbors
      // what about store the neighbors for dfs
      for (size_t ix = 0; ix < s.length(); ++ix) {
	auto &candidate = candidates[pattern(s, ix)];
	for (auto it = candidate.begin(); it != candidate.end(); ++it) {
	  // first visited
	  if (!dist.count(*it)) {
	    dist[*it] = d + 1;
	    q.push(std::make_pair(*it, d + 1));
	  }
	}
      }
    }
  }

  // passing result as argument instead of using return value
  // improve little or not
  void dfs(const std::string &now,
	   const std::string &end,
	   std::vector<std::vector<std::string>> &res,
	   std::vector<std::string> &path) {
    path.push_back(now);
    if (now == end) {
      res.push_back(path);
    } else {
      int d = dist[now];
      for (size_t ix = 0; ix < now.length(); ++ix) {
	auto &candidate = candidates[pattern(now, ix)];
	for (auto it = candidate.begin(); it != candidate.end(); ++it) {
	  if (dist[*it] == d + 1) {
	    // can't use reference to bind non-const lvalue
	    dfs(*it, end, res, path);
	  }
	}
      }
    }
    path.pop_back();
  }

  // "*234": ["1234", "2234", ..]
  std::unordered_map<std::string, std::vector<std::string>> candidates;
  std::unordered_map<std::string, int> dist;
};

std::string mkString(const std::vector<std::string> &vt,
		     const std::string beg = "[",
		     const std::string sep = ",",
		     const std::string end = "]") {
  std::string ans = beg;
  for (auto it = vt.begin(); it != vt.end(); ++it) {
    if (it != vt.begin()) {
      ans += sep;
    }
    ans += *it;
  }
  return ans + end;
}

int main() {
  Solution sol;
  std::unordered_set<std::string> dict {"hot", "dot", "dog", "lot", "log"};
  auto res = sol.findLadders("hit","cog", dict);
  std::vector<std::string> res_string;
  for (auto it = res.begin(); it != res.end(); ++it) {
    res_string.push_back(mkString(*it));
  }
  std::cout << mkString(res_string, "[\n  ", ",\n  ", "\n]\n") << std::endl;
  return 0;
}
