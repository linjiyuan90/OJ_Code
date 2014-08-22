#include "vector"
#include "unordered_map"
#include "limits"
#include "queue"

struct Graph {
  std::unordered_map<int, std::vector<int>> edges;
  std::unordered_map<int, int> dist;

public:
  void addEdge(int a, int b) {
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  
  int shortestPath(int s, int t) {
    dist.clear();
    std::queue<int> q;
    q.push(s);
    for (dist[s] = 1; !q.empty(); ) {
      int u = q.front();
      q.pop();
      for (auto& v : edges[u]) {
        if (!dist.count(v)) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
        if (v == t) {
          return dist[v];
        }
      }
    }
    return -1;
  }
};

int solution(vector<int> &A) {
  // Construct B from A, that B[0] = A[0], B[m-1] = A[n-1], and every adjacent pair in B[i, i+1]
  // is also an adjacent pair in A[j, j+1]
  // that's B[i] = A[j], B[i+1] = A[j+1], or B[i] = A[j+1], B[i+1] = A[j];
  
  // Construct a graph with value A[i] as node label and connect A[i], A[i-1]
  // then do a bfs to find a shortes path from A[0] to A[i]
  if (A.size() <= 1) {
    return A.size();
  }
  Graph graph;
  std::size_t n = A.size();
  for (std::size_t i = 0; i < n-1; ++i) {
    graph.addEdge(A[i], A[i+1]);
  }
  return graph.shortestPath(A[0], A[n-1]);
}
