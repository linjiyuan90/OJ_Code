/*
  Given a tree, remove as many edges as possible to make every component contains
  a even number of vertices.
  
  Let odd[u], even[u] means the max edges can be removed in the tree rooted at u
  such that the component connected u has odd/even number of vertices.
  
  odd[u] = 0
  even[u] = MIN
  for v in childrenOf(u):
    odd[u] = max{odd[u] + even[v] + 1, odd[v] + even[u]}
    even[u] = max{even[u] + even[v] + 1, odd[v] + odd[u]}

  How to encapsulate TreeNode and make the code both simple and beautiful?
*/

#include "iostream"
#include "vector"
#include "limits"

typedef std::vector<int> int_vector;
typedef std::vector<int_vector> int_vector2;

const int MIN = -10086;

int most_removal(int u, 
                 int_vector2& edges, 
                 int_vector& mark,
                 int_vector& odd,
                 int_vector& even) {
  mark[u] = 1;
  odd[u] = 0;
  even[u] = MIN;
  for (auto& v : edges[u]) {
    if (mark[v]) {
      continue;
    }
    most_removal(v, edges, mark, odd, even);
    int odd_u = odd[u], even_u = even[u];
    odd[u] = std::max(odd[v] + even_u, even[v] + 1 + odd_u);
    even[u] = std::max(odd[v] + odd_u, even[v] + 1 + even_u);
  }
  return even[u];
}

int main() {
  for (int n, m; std::cin >> n >> m; ) {
    int_vector2 edges(n);
    for (int i = 0, u, v; i < m; ++i) {
      std::cin >> u >> v;
      --u;
      --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    int_vector mark(n);
    int_vector odd(n), even(n);
    int res = 0;
    for (int u = 0; u < n; ++u) {
      if (!mark[u]) {
	res += most_removal(u, edges, mark, odd, even);
      }
    }
    std::cout << res << std::endl;
  }
  return 0;
}
