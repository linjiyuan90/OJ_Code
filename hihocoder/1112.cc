/*
  Given a tree, each node has a value. How many pairs of nodes (u, v) in which u < v are there that satisfy the condition that 
  the least value on the path from u to v is not c but the 2nd-least value on the path is exactly C.
*/
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Tree {
  int n_;
  vector<int> values_;
  vector< vector<int> > edges_;
  // 4 states:
  // 0, min < c & second min = c
  // 1, min < c & second min > c
  // 2, min = c
  // 3, min >= c
  // note, state 0 need at least 2 nodes.
  vector< vector<int> > nodes_;

  int64_t numOfWays(int u, int p, int c) {
    // init
    if (values_[u] < c) {
      // note this!
      // regard second min as MAX
      ++nodes_[u][1];
    } else if (values_[u] == c) {
      ++nodes_[u][2];
      ++nodes_[u][3];
    } else if (values_[u] > c) {
      ++nodes_[u][3];
    }
    int64_t ways = 0;
    for (vector<int>::iterator it = edges_[u].begin(); it != edges_[u].end(); ++it) {
      int v = *it;
      if (v == p) {
        continue;
      }
      ways += numOfWays(v, u, c);
      ways += 1ll * nodes_[u][0] * nodes_[v][3] + 1ll * nodes_[u][3] * nodes_[v][0];
      ways += 1ll * nodes_[u][1] * nodes_[v][2] + 1ll * nodes_[u][2] * nodes_[v][1];
      if (values_[u] < c) {
        nodes_[u][0] += nodes_[v][2];
        nodes_[u][1] += nodes_[v][3] - nodes_[v][2];
      } else if (values_[u] == c) {
        nodes_[u][0] += nodes_[v][0] + nodes_[v][1];
        nodes_[u][2] += nodes_[v][3];
        nodes_[u][3] += nodes_[v][3];
      } else {
        nodes_[u][0] += nodes_[v][0];
        nodes_[u][1] += nodes_[v][1];
        nodes_[u][2] += nodes_[v][2];
        nodes_[u][3] += nodes_[v][3];
      }
    }
    return ways;
  }

public:
  Tree(int n) : n_(n), values_(n), edges_(n) {
  }
  void setValue(int u, int v) {
    values_[u] = v;
  }
  void addEdge(int u, int v) {
    edges_[u].push_back(v);
    edges_[v].push_back(u);
  }
  int64_t numOfWays(int c) {
    nodes_.assign(n_, vector<int>(4, 0));
    return numOfWays(0, -1, c);
  }
};

int main() {
  for (int n, c; cin >> n >> c;) {
    Tree tree(n);
    for (int v, i = 0; i < n; ++i) {
      cin >> v;
      tree.setValue(i, v);
    }
    for (int i = 1, u, v; i < n; ++i) {
      cin >> u >> v;
      tree.addEdge(u-1, v-1);
    }
    cout << tree.numOfWays(c) << endl;
  }
  return 0;
}
