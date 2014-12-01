#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename Container, typename T>
bool contains(const Container& c, const T& v) {
  return find(c.begin(), c.end(), v) != c.end();
}

struct TreeNode {
  vector<TreeNode*> children;
  int label;
  TreeNode(int label): label(label) {
  }
};

class Tree {
  int n_;
  vector<TreeNode*> nodes_;

  vector<int> getOrders(TreeNode* root, TreeNode* pa) {
    vector<int> orders(1, root->label);
    for (int i = 0; i < root->children.size(); ++i) {
      if (root->children[i] != pa) {
        vector<int> subOrders = getOrders(root->children[i], root);
        orders.insert(orders.end(), subOrders.begin(), subOrders.end());
      }
    }
    return orders;
  }

  bool canVisit_(TreeNode* cur, TreeNode* pa, const vector<int>& orders) {
    vector<int>::const_iterator it = orders.begin();
    if (it != orders.end() && *it == cur->label) {
      ++it;
    }
    vector<pair<TreeNode*, vector<int> > > subOrders;
    for (int i = 0; i < cur->children.size(); ++i) {
      if (cur->children[i] != pa) {
        subOrders.push_back(make_pair(cur->children[i], getOrders(cur->children[i], cur)));
      }
    }
    while (!subOrders.empty() && it != orders.end()) {
      int that = -1;
      for (int c = 0; c < subOrders.size(); ++c) {
        if (contains(subOrders[c].second, *it)) {
          that = c;
          break;
        }
      }
      if (that == -1) {
        break;
      }
      vector<int>::const_iterator pre = it;
      while(it != orders.end() && contains(subOrders[that].second, *it)) {
        ++it;
      }
      if (!canVisit_(subOrders[that].first, cur, vector<int>(pre, it))) {
        return false;
      }
      subOrders.erase(subOrders.begin() + that);
    }
    return it == orders.end();
  }

 public:
  Tree(int n) : n_(n), nodes_(n) {
    for (int i = 0; i < n_; ++i) {
      nodes_[i] = new TreeNode(i);
    }
  }
  void add(int u, int v) {
    nodes_[u]->children.push_back(nodes_[v]);
    nodes_[v]->children.push_back(nodes_[u]);
  }
  bool canVisit(const vector<int>& orders) {
    return canVisit_(nodes_[0], nodes_[0], orders);
  }
};

int main() {
  int T, n;
  for (cin >>T; T--;) {
    cin >> n;
    Tree tree(n);
    for (int i = 0, u, v; i < n - 1; ++i) {
      cin >> u >> v;
      tree.add(u-1, v-1);
    }
    cin >> n;
    vector<int> orders(n);
    for (int i = 0; i < n; ++i) {
      cin >> orders[i];
      -- orders[i];
    }
    cout << (tree.canVisit(orders) ? "YES" : "NO") << endl;
  }
  return 0;
}
