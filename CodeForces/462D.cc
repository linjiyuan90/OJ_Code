/*
  Given a tree, some nodes are black and some are white.
  Count the number of ways to cut edges which make each component has only one black node.
  One way is defined as the set of edges to cut.

  Define black/white[u] as the ways to make the component of u as black/white after cutting.
  if color[u] is black
    white[u] = 0
    black[u] = prod(black[v] + white[v]), v \in u's children, that's cut edge u-v or not
  else
    white[u] = prod(black[v] + white[v])
    black[u] = sum{prod((white[v] + black[v]) * black[v'])}, v' is one of u's children
*/
#include "iostream"
#include "vector"
#include "algorithm"

class Tree {
  std::vector<std::vector<int>> edges;
  std::vector<int> colors;
  std::vector<int> white;
  std::vector<int> black;
  int n;

  void splitWays(int u, int p) {
    // think it as leaf first
    white[u] = 1 - colors[u];
    black[u] = colors[u];
    for (auto& v : edges[u]) {
      if (v == p) {
        continue;
      }
      splitWays(v, u);
      if (colors[u]) {
        white[u] = 0;
        // remain or cut
        black[u] = (1ll * black[u] * (white[v] + black[v])) % Mod;
      } else {
        // remain one, and cut others
        black[u] = (1ll * black[u] * (white[v] + black[v]) % Mod + 1ll * white[u] * black[v] % Mod) % Mod;
        // remain or cut
        white[u] = (1ll * white[u] * (white[v] + black[v])) % Mod;
      }
    }
  }

 public:
  Tree(int n): n(n) {
    edges.resize(n);
    colors.resize(n);
    white.resize(n);
    black.resize(n);
  }

  void addEdge(int u, int v) {
    edges[u].push_back(v);
    edges[v].push_back(u);
  } 
  
  int splitWays() {
    splitWays(0, 0);
    return black[0];
  }

  friend std::istream& operator>>(std::istream& is, Tree& tree) {
    for (int u = 1, v; u < tree.n; ++u) {
      std::cin >> v;
      if (v != u) {
        tree.addEdge(u, v);
      }
    }
    for (auto& c : tree.colors) {
      std::cin >> c;
    }
    return is;
  }

  static const int Mod = 1000000007;
};

int main() {
  for (int n; std::cin >> n; ) {
    Tree tree(n);
    std::cin >> tree;
    std::cout << tree.splitWays() << std::endl;
  }
  return 0;
}
