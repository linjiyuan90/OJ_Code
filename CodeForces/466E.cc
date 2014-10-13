/*
  3 types of operations:
  1) make y as the parent of x
  2) make x and all its ancestors signed one document d
  3) query whether x has signed document d
  n <= 10^5
  
  http://codeforces.com/blog/entry/13758
  Statement:
  1) let z is the people accept document d, for query (d, x), 
     that's to query whether x is ancestor of z in current tree
  2) to judge whether z is the ancetors of x, juedge whether z 
     and x in same component of current tree and z is ancestor 
     of x in the **final tree**.
  
  This lead to an offline algorihtm. First, scan all the operations
  and build a final tree. Then rescan, use disjoint-set to record
  current component.
*/
#include "numeric"
#include "iostream"
#include "vector"
#include "algorithm"
#include "unordered_map"
#include "iterator"

struct Operation {
  int type;
  int x, y;
};

class DisjointSet {
  std::vector<int> pa;
public:
  DisjointSet(int n): pa(n) {
    std::iota(pa.begin(), pa.end(), 0);
  }

  bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) {
      return false;
    }
    pa[u] = v;
    return true;
  }
  
  int find(int u) {
    return u == pa[u] ? u : pa[u] = find(pa[u]);
  }
};

class Tree {
  int n;
  std::vector<int> inDeg;
  std::vector<int> in;
  std::vector<int> out;
  std::vector<std::vector<int>> children;

  void dfs(int u, int& c) {
    in[u] = c++;
    for (auto& v : children[u]) {
      dfs(v, c);
    }
    out[u] = c++; 
  }
  
public:
  
  Tree(int n): n(n), inDeg(n), in(n, -1), out(n, -1), children(n) {
  }
  
  // u's parent is p
  void addParent(int u, int p) {
    ++inDeg[u];
    children[p].push_back(u);
  }

  // dfs to calculate in, out
  void init() {
    int c = 0;
    for (int u = 0; u < n; ++u) {
      if (inDeg[u] == 0) {
        dfs(u, c);
      }
    }
  }

  // is u ancesstor of v
  bool isAncestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
  }
};

Tree buildTree(int n, const std::vector<Operation>& operations) {
  Tree tree(n);
  for (auto& op : operations) {
    if (op.type == 1) {
      tree.addParent(op.x-1, op.y-1);
    }
  }
  tree.init();
  return tree;
}

void run(int n, const std::vector<Operation>& operations) {
  // build the final tree
  auto tree = buildTree(n, operations);
  std::unordered_map<int, std::vector<std::pair<int, Operation>>> query;
  std::vector<int> acceptDoc;
  int numQuery = 0;
  for (auto& op : operations) {
    if (op.type == 3) {
      query[op.y-1].push_back({numQuery++, op});
    }
    if (op.type == 2) {
      acceptDoc.push_back(op.x-1);
    }
  }
  std::vector<bool> ans(numQuery);
  DisjointSet ds(n);
  int d = 0;
  for (auto& op : operations) {
    if (op.type == 1) {
      ds.merge(op.x-1, op.y-1);
    } else if (op.type == 2) {
      // for any query that sign doc d, check all the query about d
      for (auto& p : query[d]) {
        int qi = p.first;
        auto& op_ = p.second;
        int x = op_.x-1;
        int z = acceptDoc[op_.y-1];
        ans[qi] = ds.find(x) == ds.find(z) && tree.isAncestor(x, z);
      }
      ++d;
    }
  }
  for (const auto& b : ans) {
    std::cout << (b ? "YES" : "NO") << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  for (int n, m; std::cin >> n >> m;) {
    std::vector<Operation> operations(m);
    for (auto& op : operations) {
      std::cin >> op.type >> op.x;
      if (op.type != 2) {
        std::cin >> op.y;
      }
    }
    run(n, operations);
  }
  return 0;
}
