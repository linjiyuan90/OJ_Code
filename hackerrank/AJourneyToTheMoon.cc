#include "iostream"
#include "vector"

void dfs(int u,
	 const std::vector<std::vector<int>> &graph,
	 std::vector<int> &id) {
  for (auto v : graph[u]) {
    if (id[v] == -1) {
      id[v] = id[u];
      dfs(v, graph, id);
    }
  }
}

int main() {
  // std::ios::sync_with_stdio(false);
  for (int n, m; std::cin >> n >> m; ) {
    std::vector<std::vector<int>> graph(n);
    for (int i = 0, a, b; i < m; ++i) {
      std::cin >> a >> b;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }
    // id the country
    std::vector<int> id(n, -1);
    int num = 0;
    for (int i = 0; i < n; ++i) {
      if (id[i] == -1) {
	id[i] = num++;
	dfs(i, graph, id);
      }
    }
    // count the number of node in each country
    std::vector<int> id_num(num);
    int max_num = 0; // the largest country
    for (int i = 0; i < n; ++i) {
      max_num = std::max(max_num, ++id_num[id[i]]);
    }
    // count how many country that with size i
    std::vector<int> size_country(max_num + 1);
    for (int i = 0; i < num; ++i) {
      ++size_country[id_num[i]];
    }
    long long ans = 0;
    for (int i = 1; i <= max_num; ++i) {
      if (size_country[i] == 0) {
	continue;
      }
      ans += (long long) size_country[i] * (size_country[i] - 1) / 2* i * i;
      for (int j = i + 1; j <= max_num; ++j) {
	ans += (long long) size_country[i] * i * size_country[j] * j;
      }
    }

    // note if there are too many samll the groups
    // for (a, b in groups)
    // will lead to TLE!
    // 100000 2
    // 1 2
    // 3 4
    std::cout << ans << std::endl;
  }
  return 0;
}
