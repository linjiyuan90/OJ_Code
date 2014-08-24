/*
  Given an undirected graph, each node has a zip code, find a minimum zip code 
  path that traverse all nodes.
  n <= 50

  Official solution:
  First, start at the node with minimum zip code. Then when choosing next node, 
  find the one with minimum zip code. Check before choose next node, make sure 
  aftering choosing it, the left nodes can still reachable!

  Using a stack to record current active path. Also, record the dead nodes.
  When choosing next node, pop current path(insert the top to dead nodes) and
  find next minimum; if the graph is not connected, break.

  Enlighten:
  1) use stack to record paths. the nodes in the stack is a path.
  2) after pop, the node become dead nodes
*/
#include "string"
#include "set"
#include "iostream"
#include "vector"
#include "stack"
#include "map"

class Graph {
  std::map<int, std::vector<int>> edges;
  std::map<int, std::string> zips;

  // simply use the stack to dfs
  bool checkReachable(std::stack<int> activePath, std::set<int> visitNodes) {
    while (!activePath.empty()) {
      int u = activePath.top();
      activePath.pop();
      for (auto& v : edges[u]) {
        if (!visitNodes.count(v)) {
          activePath.push(v);
          visitNodes.insert(v);
        }
      }
    }
    return visitNodes.size() == zips.size();
  }
  
  int nextMinNode(std::stack<int> activePath, std::set<int> visitNodes) {
    for (auto _ = activePath; !_.empty(); ) {
      visitNodes.insert(_.top());
      _.pop();
    }
    int min = -1;
    while(!activePath.empty()) {
      int cur = activePath.top();
      for (auto& next : edges[cur]) {
        if (!visitNodes.count(next)) {
          if (min == -1 || zips[min] > zips[next]) {
            min = next;
          }
        }
      }
      activePath.pop();
      if (!checkReachable(activePath, visitNodes)) {
        break;
      }
    }
    return min;
  }
  
public:
  void addEdge(int a, int b) {
    edges[a].push_back(b);
    edges[b].push_back(a);
  }
  
  void addZip(int a, const std::string& zip) {
    zips[a] = zip;
  }
  
  std::string minZipTrip() {
    int start = std::min_element(zips.begin(), zips.end(),
                                 [](const std::pair<int, std::string>& a, 
                                    const std::pair<int, std::string>& b) {
                                   return a.second < b.second;
                                 })->first;
    std::string ans = zips[start];
    std::stack<int> activePath;
    std::set<int> deadNodes;
    for (activePath.push(start); !activePath.empty(); ) {
      int u = activePath.top();
      int next = nextMinNode(activePath, deadNodes);
      if (next == -1 || std::count(edges[u].begin(), edges[u].end(), next) == 0) {
        deadNodes.insert(u);
        activePath.pop();
      } else {
        ans += zips[next];
        activePath.push(next);
      }
    }
    return ans;
  }
};

int main() {
  int T, t = 1, n, m;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n >> m;
    Graph graph;
    std::string zip;
    for (int i = 1; i <= n; ++i) {
      std::cin >> zip;
      graph.addZip(i, zip);
    }
    for (int i = 0, u, v; i < m; ++i) {
      std::cin >> u >> v;
      graph.addEdge(u, v);
    }
    std::cout << graph.minZipTrip() << std::endl;
  }
  return 0;
}
