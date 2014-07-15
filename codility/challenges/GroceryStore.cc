// you can use includes, for example:
// #include <algorithm>
typedef std::pair<int, int> IntPair;

std::vector<int> dijkstra(int n, int s, const std::vector<std::vector<IntPair>>& edges) {
    std::vector<int> dist(n, -1);
    std::vector<bool> mark(n);
    dist[s] = 0;
    for (int i = 0; i < n; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (mark[j] || dist[j] == -1) {
                continue;
            }
            if (u == -1 || dist[u] > dist[j]) {
                u = j;
            }
        }
        if (u == -1) {
            break;
        }
        mark[u] = true;
        for (auto& e : edges[u]) {
            if (dist[e.first] == -1 || dist[e.first] > dist[u] + e.second) {
                dist[e.first] = dist[u] + e.second;
            }
        }
    }
    return dist;
}

int solution(const vector<int> &A, const vector<int> &B, const vector<int> &C, const vector<int> &D) {
    int n = D.size();
    int m = A.size();
    std::vector<std::vector<IntPair>> edges(n);
    for (int i = 0; i < m; ++i) {
        edges[A[i]].push_back({B[i], C[i]});
        edges[B[i]].push_back({A[i], C[i]});
    }
    auto dist = dijkstra(n, 0, edges);
    int res = -1;
    for (int i = 0; i < n; ++i) {
        if (dist[i] != -1 && dist[i] <= D[i]) {
            res = res == -1 ? dist[i] : std::min(res, dist[i]);
        }
    }
    return res;
}
