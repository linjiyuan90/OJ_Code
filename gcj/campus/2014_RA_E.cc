#include "iostream"
#include "string"
#include "vector"
#include "map"
#include "unordered_map"
#include "limits"

class Graph {
  const int Max = std::numeric_limits<int>::max()/2;

  std::unordered_map<std::string, int> color2Id;
  std::vector<std::string> roomColor;
  std::vector<std::vector<int>> edges;
  int n_, m_;

public:
  Graph(int n): n_(n), m_(0), roomColor(n) {
  }

  void addComponent(const std::string& color, int id) {
    roomColor[id] = color;
    if (!color2Id.count(color)) {
      color2Id.insert({color, m_++});
    }
  }
  
  void init() {
    edges.resize(m_, std::vector<int>(m_, Max));
  }

  void addEdge(int a, int b, int c) {
    a = color2Id[roomColor[a]];
    b = color2Id[roomColor[b]];
    edges[a][b] = std::min(edges[a][b], c);
  }
  
  void fullSourceShortestPaths() {
    for (int k = 0; k < m_; ++k) {
      for (int i = 0; i < m_; ++i) {
        for (int j = 0; j < m_; ++j) {
          edges[i][j] = std::min(edges[i][j], edges[i][k] + edges[k][j]);
        }
      }
    }
  }
  
  // using Wall's algorithm
  int shortestPath(int a, int b) {
    a = color2Id[roomColor[a]];
    b = color2Id[roomColor[b]];
    if (a == b) {
      return 0;
    }
    return edges[a][b] == Max ? -1 : edges[a][b];
  }
  
};

int main() {
  int T, n, m, t = 1;
  std::string color;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": " << std::endl;
    std::cin >> n;
    Graph graph(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> color;
      graph.addComponent(color, i);
    }
    graph.init();
    std::cin >> m;
    for (int i = 0, a, b, c; i < m; ++i) {
      std::cin >> a >> b >> c;
      graph.addEdge(a-1, b-1, c);
    }
    graph.fullSourceShortestPaths();
    std::cin >> m;
    for (int i = 0, a, b; i < m; ++i) {
      std::cin >> a >> b;
      std::cout << graph.shortestPath(a-1, b-1) << std::endl;
    }
  }
  return 0;
}
