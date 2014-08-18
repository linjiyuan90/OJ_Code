#include "unordered_map"
#include "unordered_set"
#include "iostream"
#include "vector"
#include "string"

template <class A, class B>
struct PairHash {
  std::hash<A> aHash;
  std::hash<B> bHash;
  std::size_t operator()(const std::pair<A, B>& pair) const {
    return aHash(pair.first) ^ bHash(pair.second);
  }
};

class Graph {
  std::unordered_map<std::string, std::unordered_map<std::string, int>> edges;
  // 0 for a + b
  // 1 for a - b
  std::unordered_map<std::pair<std::string, std::string>,
                     std::pair<bool, int>,
                     PairHash<std::string, std::string>> query_cache[2];
  std::unordered_set<std::pair<std::string, std::string>, 
                     PairHash<std::string, std::string>> mark[2];

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
    // a + b
    query_cache[0][{a, b}] = {true, w};
    query_cache[0][{b, a}] = {true, w};
    // a - a
    query_cache[1][{a, a}] = {true, 0};
    query_cache[1][{b, b}] = {true, 0};
  }

  std::pair<bool, int> query(const std::string& exp) {
    std::size_t p = exp.find("+");
    const std::string& a = exp.substr(0, p);
    const std::string& b = exp.substr(p+1);
    mark[0].clear();
    mark[1].clear();
    auto q = query(a, b, 0);
    if (q.first) {
      return q;
    }
    // another situation!
    auto qa = query(a, a, 0);
    auto qb = query(b, b, 0);
    if (qa.first && qb.first) {
      q = query_cache[0][{a, b}] = {true, (qa.second + qb.second)/2};
    }
    return q;
  }

  std::pair<bool, int> 
  query(const std::string& a, const std::string& b, int flag) {
    if (query_cache[flag].count({a, b})) {
      return query_cache[flag][{a, b}];
    }
    for (auto& e : edges[a]) {
      if (mark[flag].count({a, e.first})) {
        continue;
      }
      mark[flag].insert({a, e.first});
      auto q = query(e.first, b, !flag);
      if (q.first) {
        // a flag b = (a + e) - (e !flag b)
        return query_cache[flag][{a, b}] = {true, e.second - q.second};
      }
    }
    // note --!
    return {false, 0};
  }
};

// and note different length of cycle is different!
// It can be a + a, or a - a!!!

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
