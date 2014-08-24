/*
  For each node in a tree find the sum of distances to all other nodes.
  Just 2 dfs.
*/
#include "algorithm"
#include "vector"
#include "iostream"

using namespace std;

class Tree {
  std::vector<std::vector<int>> edges;
  // when it's a line, use int will overflow
  std::vector<long long> totalLength;
  std::vector<int> totalSize;

  void sumDfs(int u, int p) {
    totalLength[u] = 0;
    totalSize[u] = 1;
    for (auto& v : edges[u]) {
      if (v != p) {
        sumDfs(v, u);
        totalSize[u] += totalSize[v];
        totalLength[u] += totalLength[v] + totalSize[v];
      }
    }
  }
  
  void centerDfs(int u, int p) {
    if (u != p) {
      int n = edges.size();
      int that = n - totalSize[u];
      totalLength[u] = totalLength[p] + that - totalSize[u];
    }
    for (auto& v : edges[u]) {
      if (v != p) {
        centerDfs(v, u);
      }
    }
  }
  
public:
  Tree(int n) {
    totalLength.resize(n);
    totalSize.resize(n);
    edges.resize(n);
  }

  void addEdge(int a, int b) {
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  
  int minPeripheralityLabel() {
    sumDfs(0, 0);
    centerDfs(0, 0);
    return 
      std::min_element(totalLength.begin(), totalLength.end()) 
      - totalLength.begin();
  }
};

int solution(vector<int> &T) {
  Tree tree(T.size());
  for (int i = 0, n = T.size(); i < n; ++i) {
    if (i != T[i]) {
      tree.addEdge(i, T[i]);
    }
  }
  return tree.minPeripheralityLabel();
}
