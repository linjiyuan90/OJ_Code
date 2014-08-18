#include "map"
#include "set"
#include "iostream"
#include "vector"
#include "string"

class Graph {
  std::map<std::string, std::map<std::string, int>> edges;
  std::set<std::tuple<std::string, std::string, bool>> visit;

public:
  void addEdge(const std::string& a, const std::string& b, int w) {
    edges[a][b] = w;
    edges[b][a] = w;
  }

  void addEdge(const std::string& exp) {
    std::size_t p = exp.find("+");
    const std::string& a = exp.substr(0, p);
    std::size_t q = exp.find("=");
    const std::string& b = exp.substr(p+1, q - p - 1);
    int w = std::stoi(exp.substr(q+1));
    addEdge(a, b, w);
  }

  std::pair<bool, int> query(const std::string& exp) {
    std::size_t p = exp.find("+");
    const std::string& a = exp.substr(0, p);
    const std::string& b = exp.substr(p+1);
    visit.clear();
    auto q = query(a, b, 0, 0);
    if (q.first) {
      return q;
    }
    // another situation!
    auto qa = query(a, a, 0, 0);
    auto qb = query(b, b, 0, 0);
    if (qa.first && qb.first) {
      return {true, (qa.second + qb.second)/2};
    }
    return q;
  }

  std::pair<bool, int> 
  query(const std::string& a, const  std::string& b, int sum, int flag) {
    if (a == b && flag) {
      return {flag, sum};
    }
    for (auto& e : edges[a]) {
      if (visit.count({a, e.first, flag})) {
        continue;
      }
      visit.insert({a, e.first, flag});
      auto q = query(e.first, b, sum + (flag ? -e.second : e.second), !flag);
      if (q.first) {
        return q;
      }
    }
    return {false, 0};
  }
};

int main() {
  int T, t = 1, n;
  std::string exp;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ":" << std::endl;
    Graph graph;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
      std::cin >> exp;
      graph.addEdge(exp);
    }
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
      std::cin >> exp;
      auto q = graph.query(exp);
      if (q.first) {
        std::cout << exp << "=" << q.second << std::endl; 
      }
    }
  }
  return 0;
}
