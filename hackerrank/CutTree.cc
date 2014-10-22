/*
  How many ways to cut a subtree that has at most k edges to connect with the remaining part.

  Let cut[u] be the number of ways with restriction that u has been cut from its parent.
  Let connect[u, k] be the number of ways to cut k parts of u's subtree (and u is not cut from its parent), then
  connect[u, k] = ∏(connect[v, kv] + (kv == 1 ? 1 : 0)), where v is u's son, ∑kv = k
  cut[u] = ∑connect[u, k'], k' = 0..k-1, if u is root, k' can be k
  
  The answer will be:
  1 + ∑cut[u]
*/
#include "numeric"
#include "iostream"
#include "vector"
#include "algorithm"

class Tree {
  int n_;
  std::vector<std::vector<int>> edges;
  std::vector<int64_t> cut;
  std::vector<std::vector<int64_t>> connect;

  void dfs(int u, int p, int k) {
    connect[u][0] = 1;
    for (auto& v : edges[u]) {
      if (v == p) {
        continue;
      }
      dfs(v, u, k);
      for (int ku = k; ku >= 0; --ku) {
        int64_t sum = 0;
        for (int kv = 0; kv <= ku; ++kv) {
          sum += connect[u][ku-kv] * (connect[v][kv] + (kv == 1 ? 1 : 0));
        }
        connect[u][ku] = sum;
      }
    }
    cut[u] = std::accumulate(connect[u].begin(), connect[u].begin() + k, 0ll);
  }
  
public:
  Tree(int n): n_(n), edges(n) {
  }
  void add(int u, int v) {
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  int64_t cutWays(int k) {
    cut.assign(n_, 0);
    connect.assign(n_, std::vector<int64_t>(k+1));
    dfs(0, 0, k);
    cut[0] += connect[0][k];
    // add an empty subtree!
    return 1 + std::accumulate(cut.begin(), cut.end(), 0ll);
  }
};

int main() {
  for (int n, k, u, v; std::cin >> n >> k; ) {
    Tree tree(n);
    for (int i = 0; i < n - 1; ++i) {
      std::cin >> u >> v;
      tree.add(u-1, v-1);
    }
    std::cout << tree.cutWays(k) << std::endl;
  }
  return 0;
}
