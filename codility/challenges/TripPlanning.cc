/*
  Given a tree. Start at K, at each time, go the node which maximize unvisited nodes during the path.
  In case of tie, choose the smaller node.
  Design an O(n) algorithm to find the vistied node in sequential.

  DON'T simulate the process, using dfs to find longest path from the root of
  each subtree.  Then add one to the longest path, since the longest
  path will be first visited, which has root as an unvisited node.
  
  dfs(u)
    for v in u's children
      dfs(v)
    ++length[longest_leaf]
*/

int dfs(int p, 
        int u,
        std::vector<std::vector<int>>& edge,
        std::vector<int>& length) {
  int longest = -1;
  for (auto& v : edge[u]) {
    if (v == p) {
      continue;
    }
    auto _longest = dfs(u, v, edge, length);
    if (longest == -1 
	|| length[longest] < length[_longest]
	|| (length[longest] == length[_longest] && longest > _longest)) {
      longest = _longest;
    }
  }
  if (longest == -1) { // u is leaf
    longest = u;
  }
  ++ length[longest];
  return longest;
}

vector<int> solution(int K, vector<int>& T) {
  int n = T.size();
  std::vector<std::vector<int>> edge(n);
  for(int u = 0; u < n; ++u) {
    if (u == T[u]) {
      continue;
    }
    edge[u].push_back(T[u]);
    edge[T[u]].push_back(u);
  }
  std::vector<int> length(n);
  dfs(K, K, edge, length);
  // sort
  std::vector<std::vector<int>> count(n+1);
  for (int u = 0; u < n; ++u) {
    count[length[u]].push_back(u);
  }
  std::vector<int> res {K};
  for (int i = n; i > 0; --i) {
    for (auto& u : count[i]) {
      if (u != K) {
	res.push_back(u);
      }
    }
  }
  return res;
}
