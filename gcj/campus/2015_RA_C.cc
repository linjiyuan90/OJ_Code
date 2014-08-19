/*
  Given some expressions like a+b=1, b+c=2, ...
  Query like a+c, a+d, ...
  
  Think about these expressions as undirectional graph, with variable as node and value as edge weight.
  Then an even length path means: a - b while an odd length path means a + b;
  So traverse the graph to find odd length path from a to b for query a+b
  Also, note situation where a and b are in two separate graphs. In this case, a+b = ((a+a) + (b+b))/2

  When traversing the graph, mark (u, flag) not u nor (u, v).
  mark[flag][u] means: the path **start from a** to u with odd|even length has been visited
  Cache results: (a, b, flag).

  Also, for each query, bfs will also works.

  Note different length of cycle is different! It can be a + a, or a - a!!!

  One optimization is: once find a cycle, all the numbers in the cycle has a solution:
  a + b, if the length of the cycle is odd
  a - b, if the length of the cycle is even
  But this seems don't have a huge influence

  This problem helps me impress the understanding of mark array!
  mark[v] means, **start from s**, v has been visited. (Note the precondition)
*/
#include "unordered_map"
#include "unordered_set"
#include "iostream"
#include "vector"
#include "string"
#include "queue"

template <class A, class B>
struct PairHash {
  std::hash<A> aHash;
  std::hash<B> bHash;
  const std::size_t operator()(const std::pair<A, B>& pair) const {
    return aHash(pair.first) ^ bHash(pair.second);
  }
};

class Graph {
  std::unordered_map<std::string, std::unordered_map<std::string, int>> edges;
  // 0 for a + b
  // 1 for a - b
  std::unordered_map<std::pair<std::string, std::string>,
                     int,
                     PairHash<std::string, std::string>> query_cache[2];
  std::unordered_set<std::string> mark[2];

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
    query_cache[0][{a, b}] = w;
    query_cache[0][{b, a}] = w;
    // a - a
    query_cache[1][{a, a}] = 0;
    query_cache[1][{b, b}] = 0;
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
    // another situation: a+b = ((a+a) + (b+b))/2
    auto qa = query(a, a, 0);
    auto qb = query(b, b, 0);
    if (qa.first && qb.first) {
      q = {true, query_cache[0][{a, b}] = (qa.second + qb.second)/2};
    }
    return q;
  }

  std::pair<bool, int> 
  query(const std::string& a, const std::string& b, int flag) {
    return queryDFS(a, b, flag);
    // return queryBFS(a, b, flag);
  }

  // query by bfs
  std::pair<bool, int>
  queryBFS(const std::string& a, const std::string& b, int flag) {
    if (query_cache[flag].count({a, b})) {
      return {true, query_cache[flag][{a, b}]};
    }
    std::queue<std::pair<std::string, int>> q;
    q.push({a, 1});  // a - a
    while(!q.empty()) {
      const std::string u = q.front().first;
      bool f = q.front().second;
      int value = query_cache[f][{a, u}];
      q.pop();
      if (b == u && f == flag) {
        return {true, value};
      }
      for (auto& e : edges[u]) {
        // using insert is more beautiful
        if (mark[f].insert(e.first).second) {
          q.push({e.first, !f});
          // a + e = a - u + u + e
          // a - e = a + u - (u + e)
          query_cache[!f].insert({
              {a, e.first}, (f ? value + e.second : value - e.second)}
            );
        }
      }
    }
    return {false, 0};
  }

  // query by dfs, and store (u, v, flag), not (a, v, flag)
  std::pair<bool, int> 
  queryDFS(const std::string& a, const std::string& b, int flag) {
    if (query_cache[flag].count({a, b})) {
      return {true, query_cache[flag][{a, b}]};
    }
    for (auto& e : edges[a]) {
      if (mark[flag].insert(e.first).second) {
        auto q = queryDFS(e.first, b, !flag);
        if (q.first) {
          // a flag b = (a + e) - (e !flag b)
          return {true, query_cache[flag][{a, b}] = e.second - q.second};
        }
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
