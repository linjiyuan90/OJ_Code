#include "iostream"
#include "string"
#include "vector"
#include "list"
#include "map"

using namespace std;

class Graph {
  std::vector<std::list<int>> edges;
  
public:
  void addEdge(int u, int v) {
    int s = std::max(u, v);
    if (s >= edges.size()) {
      edges.resize(s+1);
    }
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  
  bool hasOddCycle(int u, std::vector<int>& mark, int flag) {
    mark[u] = flag;
    int thatFlag = 3 - flag;
    for (auto& v : edges[u]) {
      if (mark[v] == flag ||
          (mark[v] == 0 && hasOddCycle(v, mark, thatFlag))) {
        return true;
      }
    }
    return false;
  }
  
  bool hasOddCycle() {
    int n = edges.size();
    std::vector<int> mark(n);
    for (int u = 0; u < n; ++u) {
      if (mark[u] == 0) {
        if (hasOddCycle(u, mark, 1)) {
          return true;
        }
      }
    }
    return false;
  }
};

int main() {
  int T, m, t = 1;
  for (std::cin >> T; T--; ++t) {
    std::map<std::string, int> mp;
    Graph graph;
    for (std::cin >> m; m--;) {
      std::string a, b;
      std::cin >> a >> b;
      if (!mp.count(a)) {
        mp.insert({a, mp.size()});
      }
      if (!mp.count(b)) {
        mp.insert({b, mp.size()});
      }
      graph.addEdge(mp[a], mp[b]);
    }
    std::cout << "Case #" << t << ": "
              << (graph.hasOddCycle() ? "No" : "Yes")
              << std::endl;;
  }
  return 0;
}
