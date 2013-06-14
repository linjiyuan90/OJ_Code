#include "algorithm"
#include "iostream"

using namespace std;

const int MAXN = 1010;
const int INF = 2000000000;

struct Trans {
  int o, e, p;
  bool operator < (const Trans &that) const {
    return o < that.o || o == that.o && e < that.e;
  }
};

int next[MAXN], max_e[MAXN], max_p[MAXN];

void dfs (int i, vector<Trans> &trans, int p) {
  next[i] = i;
  max_e[i] = trans[i].e;
  max_p[i] = trans[i].p;
  for (int j = 0; j < trans.size(); j++) {
    if (trans[j].e <= trans[i].o || trans[j].o > trans[i].e) {
      continue;
    } 
    if (i != j) {
      dfs(j, m, min(p, trans[j].p));
    }
    if (max_e[j] > max_e[i]) {
      max_e[i] = max_e[j];
      max_p[i] = max_p[j];
      next[i] = j;
    } else if (max_e[j] == max_e[i]) {
      max_p[i] = max(max_p[i], max_p[j]);
      next[i] = j;
    }
  }
}

long long back(int i, vector<Trans> &trans) {
  long long cost = 0;
  int p = max_p[i];
  do {
    trans[i].p -= p;

  } while (i != next[i]);
}

int main() {
  int T, t = 1;
  for (cin >> T; T--; ) {
    cout << "Case #" << t++ << ": ";
    int n, m;
    cin >> n >> m;
    vector<Trans> trans(m);
    for (int i = 0; i < m; i++) {
      cin >> trans[i].o >> trans[i].e >> tran[i].p;
    }
    sort (trans.begin(), trans.end());
    long long total_cost = 0;
    while (!trans.empty()) {
      dfs(0, trans, INF);
      // find longest path
      // delete full cap node
      total_cost += back(0, trans);
    }
    cout << total_cost << endl;
  }
  return 0;
}
