/*
 Given a tree where each edge is color as 'r' or 'b'
 How many triplets (a, b, c) that there is at least one 'r' edge on the
 path (a, b), (a, c), (b, c).
 
 My solution is by 2 dfs, first from buttomup, then topdown, which is totally complicated!!!!

 https://www.hackerrank.com/challenges/kundu-and-tree/editorial
 Split the tree into forest by cuting red edges.
 The answer will be ∑a[i]*a[j]*a[k], where a[] is a componet, i != k && i != j && j != k
 
 A very interesting solution !!!

 When building the tree, can skip the 'r' edge.
*/

#include "iostream"
#include "vector"
#include "cassert"

const int Mod = 1000000007;

enum Color {
  RED, BLACK
};

class Tree {
  int n_;
  std::vector<std::vector<std::pair<int, Color>>> edges_;
  std::vector<int> labels_;

  void label(int u, int p, int l) {
    assert(labels_[u] == -1);
    labels_[u] = l;
    for (auto& vc : edges_[u]) {
      int v = vc.first;
      Color color = vc.second;
      if (v == p) {
        continue;
      }
      if (color != RED) {
        label(v, u, l);
      }
    }
  }
  
public:
  Tree(int n): n_(n), edges_(n), labels_(n) {
  }
  void add(int u, int v, Color c) {
    edges_[u].push_back({v, c});
    edges_[v].push_back({u, c});
  }
  int countTriplets() {
    std::fill(labels_.begin(), labels_.end(), -1);
    int l = 0;
    for (int u = 0; u < n_; ++u) {
      if (labels_[u] == -1) {
        label(u, u, l++);
      }
    }
    std::vector<int> componentNum(l);
    for (int u = 0; u < n_; ++u) {
      ++componentNum[labels_[u]];
    }
    int singleSum = 0;
    int pairSum = 0;
    int triplets = 0;
    for (int i = 0; i < l; ++i) {
      triplets = (triplets + 1ll * pairSum * componentNum[i] % Mod) % Mod;
      pairSum = (pairSum + 1ll * singleSum * componentNum[i] % Mod) % Mod;
      singleSum = (singleSum + componentNum[i]) % Mod;
    }
    return triplets;
  }
};

int main() {
  for (int n, u, v; std::cin >> n; ) {
    Tree tree(n);
    char color;
    for (int i = 1; i < n; ++i) {
      std::cin >> std::skipws >> u >> v >> color;
      tree.add(u-1, v-1, color == 'r' ? RED : BLACK);
    }
    std::cout << tree.countTriplets() << std::endl;
  }
  return 0;
}
