#include "algorithm"

typedef std::pair<int, int> IntPair;
typedef std::pair<int, IntPair> Edge;

int solution(int n, vector<int> &A, vector<int> &B, vector<int> &C) {
  int m = A.size();
  std::vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    edges.push_back({C[i], {A[i], B[i]}});
  }
  std::sort(edges.begin(), edges.end());
  std::vector<int> pre(n), now(n);
  std::vector<int> last_w(n);
  // group edge by w
  // same w are processed in the same round
  for (auto& edge : edges) {
    int w = edge.first;
    int u = edge.second.first, v = edge.second.second;
    if (last_w[u] != w) {
      pre[u] = now[u];
      last_w[u] = w;
    }
    if (last_w[v] != w) {
      pre[v] = now[v];
      last_w[v] = w;
    }
    now[u] = std::max(now[u], pre[v] + 1);
    now[v] = std::max(now[v], pre[u] + 1);
  }
  return *max_element(now.begin(), now.end());
}
