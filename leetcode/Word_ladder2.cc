class Solution {
public:
  vector<vector<string>> findLadders(string start,
				     string end,
				     unordered_set<string> &dict) {
    if (start == end) {
      return vector<vector<string>> {vector<string>{start, end}};
    }
    // build bidirection graph
    // label string as 0, 1, ..., n-1
    // start, end as n, n+1
    dict_vt.clear();
    dist.clear();
    G.clear();

    int n = dict.size();
    dict_vt.reserve(n+2);
    copy(dict.begin(), dict.end(), back_inserter(dict_vt));
    dict_vt.push_back(start);
    dict_vt.push_back(end);
    build_graph();

    // bfs to find shortset path
    dist.resize(n+2, INF);
    bfs(n+1);

    // dfs to get all the paths
    vector<vector<string>> res;
    vector<string> path;
    dfs(n, n+1, res, path);
    return res;
  }

private:
  // Consider every pair of point and check whether they're neighbor
  // is slow.
  // Another approach is to set one of the char as '*'
  // For example:
  // 1234 => *234, 1*234, 12*4, 123*
  void build_graph() {
    int n = dict_vt.size();
    G.resize(n);
    unordered_map<string, vector<int>> umap;
    for (size_t i = 0; i < n; i++) {
      string s = dict_vt[i];
      for (size_t j = 0; j < s.length(); j++) {
	char ch = s[j];
	s[j] = '*';
	umap[s].push_back(i);
	s[j] = ch;
      }
    }
    for (auto it = umap.begin(); it != umap.end(); it++) {
      vector<int> &vt = it->second;
      for (size_t i = 0; i < vt.size(); i++) {
	for (size_t j = i+1; j < vt.size(); j++) {
	  G[vt[i]].push_back(vt[j]);
	  G[vt[j]].push_back(vt[i]);
	}
      }
    }
  }

  void bfs(int t) {
    dist[t] = 0;
    queue<int> Q;
    Q.push(t);
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (size_t ix = 0; ix < G[u].size(); ix++) {
	int v = G[u][ix];
	if (dist[v] == INF) {
	  dist[v] = dist[u] + 1;
	  Q.push(v);
	}
      }
    }
  }

  void dfs(int u, int t, vector<vector<string>> &res, vector<string> &path) {
    path.push_back(dict_vt[u]);
    if (u == t) {
      res.push_back(path);
    } else {
      for (size_t ix = 0; ix < G[u].size(); ix++) {
	int v = G[u][ix];
	if (dist[v] == dist[u] - 1) {
	  dfs(v, t, res, path);
	}
      }
    }
    path.pop_back();
  }

  vector<string> dict_vt;
  vector<vector<int>> G;  // adjoint list
  vector<int> dist;  // dist from target

  const int INF = 0x3f3f3f3f;
};

