#include "iostream"
#include "queue"
#include "algorithm"
#include "vector"

int solution(const std::vector<int> &A,
	     const std::vector<int> &B,
	     const std::vector<int> &C,
	     const std::vector<int> &D) {
  
  typedef std::pair<int, int> PII;

  // build an adjcent list
  std::vector<std::vector<PII>> edges(D.size());
  for (size_t ix = 0, n = A.size(); ix < n; ++ix) {
    int a = A[ix], b = B[ix], c = C[ix];
    edges[a].push_back(std::make_pair(b, c));
    edges[b].push_back(std::make_pair(a, c));
  }

  std::vector<int> dist(D.size());
  std::fill(dist.begin(), dist.end(), -1);

  std::priority_queue<PII> pq;
  pq.push(std::make_pair(0, 0));
  while (!pq.empty()) {
    PII top = pq.top();
    pq.pop();
    int d = -top.first, u = top.second;
    dist[u] = d;
    // reach a store
    if (D[u] != -1 && dist[u] <= D[u]) {
      return dist[u];
    }
    for (std::vector<PII>::iterator it = edges[u].begin(); 
	 it != edges[u].end(); ++it) {
      int v = it->first, w = it->second;
      // which has been visited
      if (dist[v] != -1) {
	continue;
      }
      pq.push(std::make_pair(-(d + w), v));
    }
  }
  return -1;
}

int main() {
  std::vector<int> A{0, 1, 3, 1, 2, 2}, B{1, 2, 2, 3, 0, 1}, C{2, 3, 4, 5, 7, 5}, D{-1, 1, 3, 8};
  std::cout << solution(A, B, C, D) << std::endl;
  return 0;
}
