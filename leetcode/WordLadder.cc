class Solution {
public:
  int ladderLength(string start, string end, unordered_set<string> &dict) {
    std::queue<std::string> que;
    std::unordered_map<std::string, int> dist;
    for (que.push(start), dist[start] = 1; !que.empty(); ) {
      const std::string now = que.front();
      que.pop();
      // find its neighbors
      std::string next = now;
      for (int i = 0, n = now.size(); i < n; ++i) {
	for (char ch = 'a'; ch <= 'z'; ++ch) {
	  next[i] = ch;
	  if (ch != now[i] && dict.count(next)) {
	    if (!dist.count(next)) {
	      que.push(next);
	      dist[next] = dist[now] + 1;
	      if (next == end) {
		return dist[next];
	      }
	    }
	  }
	  next[i] = now[i];
	}
      }
    }
    return 0;
  }
};
