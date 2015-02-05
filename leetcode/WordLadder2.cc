class Solution {
    
  // bfs to find shortest paths
  void bfs_paths(
		 const std::string& start,
		 const std::string& end,
		 std::unordered_set<std::string>& dict,
		 std::unordered_map<std::string, std::vector<std::string>>& pre) {
    std::queue<std::string> que;
    std::unordered_map<std::string, int> dist;
    for (que.push(start), dist[start] = 0; !que.empty();) {
      std::string now = que.front();
      que.pop();
      if (now == end) {
	break;
      }
      std::string next = now;
      for (int i = 0, l = now.length(); i < l; ++i) {
	for (char ch = 'a'; ch <= 'z'; ++ch) {
	  next[i] = ch;
	  if (ch != now[i] && dict.count(next)) {
	    if (!dist.count(next)) {
	      que.push(next);
	      dist[next] = dist[now] + 1;
	    }
	    if (dist[next] == dist[now] + 1) {
	      pre[next].push_back(now);
	    }
	  }
	  next[i] = now[i];
	}
      }
    }
  }
    
  // trace back from end to start, not from start to end!!!
  // otherwise, there are too many useless paths
  void trace_paths(
		   const std::string& now, 
		   const std::string& start,
		   std::unordered_map<std::string, std::vector<std::string>>& pre,
		   std::vector<std::vector<std::string>>& ans,
		   std::vector<std::string>& path) {
    path.push_back(now);
    if (now == start) {
      ans.push_back(path);
      std::reverse(ans.back().begin(), ans.back().end());
    } else {
      for (auto& p : pre[now]) {
	trace_paths(p, start, pre, ans, path);
      }
    }
    path.pop_back();
  }

public:
  vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
    // no need to store a word's neighbors
    std::unordered_map<std::string, std::vector<std::string>> pre;
    // bfs the shortest path
    bfs_paths(start, end, dict, pre);
    // trace back the paths
    std::vector<std::vector<std::string>> ans;
    std::vector<std::string> path;
    trace_paths(end, start, pre, ans, path);
    return ans;
  }
};
