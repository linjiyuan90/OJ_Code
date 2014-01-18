#include "iostream"
#include "unordered_map"
#include "unordered_set"
#include "vector"
#include "string"
#include "queue"

// 1840 ms
class Solution {
public:
  typedef std::vector<std::string> VS;
  typedef std::vector<int> VI;
  typedef std::vector<VS> VVS;
  typedef std::vector<VI> VVI;

  std::vector<std::vector<std::string>> 
  findLadders(std::string start,
	      std::string end,
	      std::unordered_set<std::string> &dict) {
    if (start == end) {
      return std::vector<std::vector<std::string>> {
	std::vector<std::string>{start, end}
      };
    }
    
    int n = build_graph(dict, start, end);
    // bfs to calculate dist
    bfs(n - 2, n - 1, n);
    // dfs to generate combintion
    VVS res;
    VS path;
    dfs(n - 2, n - 1, res, path);
    return res;
  }

private:

  // much faster than using concatenation!
  std::string pattern(const std::string &s, const int &ix) {
    std::string p = s;
    p[ix] = '*';
    return p;
  }
  
  // start, end will be encoded as n + 1
  // where n is |dict|
  int build_graph(std::unordered_set<std::string> &dict,
		   const std::string &start,
		   const std::string &end) {

    // "*234": ["1234", "2234", ..]
    std::unordered_map<std::string, VI> candidates;
    // how to capture pattern?
    auto push_candidate = [&candidates](const std::string &s, const int &id) {
      std::string t = s;
      for (size_t ix = 0; ix < s.length(); ++ix) {
	t[ix] = '*';
	candidates[t].push_back(id);
	t[ix] = s[ix];
      }
    };

    int n = 0;
    for (auto s: dict) {
      word_vt.push_back(s);
      push_candidate(s, n++);
    }
    for (auto s : {start, end}) {
      word_vt.push_back(s);
      push_candidate(s, n++);
    }

    edges.resize(n);
    for (auto candidate : candidates) {
      for (auto u : candidate.second) {
	for (auto v : candidate.second) {
	  if (u != v) {
	    edges[u].push_back(v);
	  }
	}
      }
    }
    return n;
  }

  void bfs(int start, int end, int n) {
    std::queue<int> q;
    q.push(start);
    dist.resize(n);
    std::fill(dist.begin(), dist.end(), -1);
    dist[start] = 0;
    while(!q.empty()) {
      int s = q.front(), d = dist[s];
      q.pop();
      if (s == end) {
	break;
      }
      for (auto v : edges[s]) {
	if (dist[v] == -1) {
	  dist[v] = d + 1;
	  q.push(v);
	}
      }
    }
  }

  void dfs(int now, int end, VVS &res, VS &path) {
    path.push_back(word_vt[now]);
    if (now == end) {
      res.push_back(path);
    } else {
      int d = dist[now];
      for (auto v : edges[now]) {
	if (dist[v] == d + 1) {
	  dfs(v, end, res, path);
	}
      }
    }
    path.pop_back();
  }

  VS word_vt;
  VVI edges;
  VI dist;
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
  for (auto s : res) {
    res_string.push_back(mkString(s));
  }
  std::cout << mkString(res_string, "[\n  ", ",\n  ", "\n]\n") << std::endl;
  return 0;
}
