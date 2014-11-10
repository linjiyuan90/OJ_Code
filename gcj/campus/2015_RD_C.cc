#include <cassert>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Graph {
  map<string, vector<string>> edges;
  map<string, int> inDegree;
  
 public:
  void add(const string& from, const string& to) {
    edges[from].push_back(to);
    inDegree[from];
    ++inDegree[to];
  }
  vector<pair<string, string>> getRoute() {
    auto it = find_if(inDegree.begin(), inDegree.end(), [](const pair<string, int>& e) {
        return e.second == 0;
      });
    assert(it != inDegree.end());
    vector<pair<string, string>> route;
    for (string now = it->first; !edges[now].empty(); ) {
      assert(edges[now].size() == 1);
      route.push_back({now, edges[now].front()});
      now = edges[now].front();
    }
    return route;
  }
};

int main() {
  int T, t = 1, n;
  for (cin >> T; T--; t++) {
    cout << "Case #" << t << ": ";
    cin >> n;
    Graph graph;
    for (string a, b; n--; ) {
      cin >> a >> b;
      graph.add(a, b);
    }
    auto route = graph.getRoute();
    for (size_t i = 0; i < route.size(); ++i) {
      if (i > 0) {
        cout << " ";
      }
      cout << route[i].first << "-" << route[i].second;
    }
    cout << endl;
  }
  return 0;
}
