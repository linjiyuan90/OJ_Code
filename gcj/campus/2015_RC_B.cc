#include "map"
#include "numeric"
#include "queue"
#include "iostream"
#include "vector"
#include "string"
#include "bitset"
#include "algorithm"
#include "set"
#include "functional"

// use floyd to calculate all shortest path between tunnels
// then enumerate tunnels of the two metros to use

struct Station {
  int m, s;
  Station(int m, int s): m(m), s(s) {
  }
  bool operator == (const Station& that) const {
    return m == that.m && s == that.s;
  }
  bool operator < (const Station& that) const {
    return m < that.m || (m == that.m && s < that.s);
  }
};

template <class T>
class Graph {
  std::map<T, std::map<T, int>> edges;
public:
  // note, there maybe duplicate edges
  void add(const T& a, const T& b, int c) {
    if (edges[a].count(b)) {
      edges[a][b] = edges[b][a] = std::min(edges[a][b], c);
    } else {
      edges[a][b] = edges[b][a] = c;
    }
  }
  void floyd() {
    std::vector<T> nodes;
    for (const auto& e : edges) {
      nodes.push_back(e.first);
    }
    for (const auto& k : nodes) {
      for (const auto& i : nodes) {
        for (const auto& j : nodes) {
          if (i == j) {
            edges[i][j] = 0;
          } else if (edges[i].count(k) && edges[k].count(j)) {
            if (edges[i].count(j)) {
              edges[i][j] = std::min(edges[i][j], edges[i][k] + edges[k][j]);
            } else {
              edges[i][j] = edges[i][k] + edges[k][j];
            }
          }
        }
      }
    }
  }
  int dist(const T& a, const T& b) {
    return edges[a].count(b) ? edges[a][b] : -1;
  }
};

int main() {
  int T, t = 1;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ":" << std::endl;
    int N, M, Q;
    std::cin >> N;
    std::vector<std::vector<int>> metros(N);
    std::vector<int> wait(N);
    for (int i = 0, n; i < N; ++i) {
      std::cin >> n >> wait[i];
      metros[i].resize(n);
      for (int j = 1; j < n; ++j) {
        std::cin >> metros[i][j];
      }
      std::partial_sum(metros[i].begin(), metros[i].end(), metros[i].begin());
    }
    Graph<Station> graph;
    std::vector<std::set<Station>> tunnels(N);
    std::cin >> M;
    for (int i = 0, m, s, c; i < M; ++i) {
      std::cin >> m >> s;
      Station a(m-1, s-1);
      std::cin >> m >> s >> c;
      Station b(m-1, s-1);
      graph.add(a, b, c);
      tunnels[a.m].insert(a);
      tunnels[b.m].insert(b);
    }
    // add some links between tunnels of same metro
    for (int m = 0; m < N; ++m) {
      for (const auto& a : tunnels[m]) {
        for (const auto& b : tunnels[m]) {
          if (a < b) {
            graph.add(a, b, wait[m] + ::abs(metros[m][a.s] - metros[m][b.s]));
          }
        }
      }
    }
    graph.floyd();
    std::cin >> Q;
    for (int i = 0, m, s; i < Q; ++i) {
      std::cin >> m >> s;
      Station a(m-1, s-1);
      std::cin >> m >> s;
      Station b(m-1, s-1);
      int dist = a.m == b.m ? wait[a.m] + ::abs(metros[a.m][a.s] - metros[b.m][b.s]) : -1;
      for (const auto& ta : tunnels[a.m]) {
        for (const auto& tb : tunnels[b.m]) {
          int _dist = graph.dist(ta, tb);
          if (_dist != -1) {
            _dist += 
              (a == ta ? 0 : wait[ta.m]) + ::abs(metros[a.m][a.s] - metros[ta.m][ta.s])
              + (b == tb ? 0 : wait[tb.m]) + ::abs(metros[b.m][b.s] - metros[tb.m][tb.s]);
            if (dist == -1 || _dist < dist) {
              dist = _dist;
            }
          }
        }
      }
      std::cout << dist << std::endl;
    }
  }
}
