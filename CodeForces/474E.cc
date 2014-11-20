#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class Index {
  vector<T> ix_;
 public:
  Index(const vector<T>& ix): ix_(ix) {
    sort(ix_.begin(), ix_.end());
    ix_.erase(unique(ix_.begin(), ix_.end()), ix_.end());
  }
  bool contains(const T& x) const {
    return binary_search(ix_.begin(), ix_.end(), x);
  }
  int operator[](const T& x) const {
    return lower_bound(ix_.begin(), ix_.end(), x) - ix_.begin();
  }
  int size() const {
    return ix_.size();
  }
};

template<typename A, typename B>
struct FirstLess {
  bool operator () (const pair<A, B>& a, const pair<A, B>& b) const {
    return a.first < b.first;
  };
};

template<typename T>
struct SegmentTreeNode {
  T data;
  int left;
  int right;
  SegmentTreeNode* leftNode;
  SegmentTreeNode* rightNode;
  SegmentTreeNode(const T& data, 
                  const int& left,
                  const int& right, 
                  SegmentTreeNode* const& leftNode = NULL,
                  SegmentTreeNode* const& rightNode = NULL) :
    data(data), 
    left(left), right(right), 
    leftNode(leftNode), rightNode(rightNode) {
  }
};

template<typename T, typename Cmp = less<T>>
class MaxSegmentTree {
  
  typedef SegmentTreeNode<T> NodeType;
  
  Cmp dataCmp_;
  // maintain an interval in [0, size_)
  int size_;
  NodeType* root_;
  
  NodeType* buildTree(int left, int right) {
    NodeType* root = new SegmentTreeNode<T>(T(), left, right);
    if (left == right) {
      return root;
    }
    int mid = (left + right) / 2;
    root->leftNode = buildTree(left, mid);
    root->rightNode = buildTree(mid + 1, right);
    return root;
  }

  void insert(NodeType* root, const int& pos, const T& data) {
    if (root->left == pos && root->right == pos) {
      root->data = max(root->data, data, dataCmp_);
      return;
    }
    int mid = (root->left + root->right) / 2;
    if (pos <= mid) {
      insert(root->leftNode, pos, data);
    } else {
      insert(root->rightNode, pos, data);
    }
    root->data = max(root->data, data, dataCmp_);
  }

  T query(NodeType* root, const int& l, const int& r) {
    if (l <= root->left && root->right <= r) {
      return root->data;
    }
    int mid = (root->left + root->right) / 2;
    T ans;
    if (l <= mid) {
      ans = max(ans, query(root->leftNode, l, r), dataCmp_);
    }
    if (r > mid) {
      ans = max(ans, query(root->rightNode, l, r), dataCmp_);
    }
    return ans;
  }
  
 public:
  MaxSegmentTree(int size) : size_(size) {
    root_ = buildTree(0, size - 1);
  }
  
  void insert(const int& pos, const T& data) {
    if (pos < 0 || pos >= size_) {
      return;
    }
    insert(root_, pos, data);
  }
  
  T query(int l, int r) {
    l = max(0, l);
    r = min(r, size_ - 1);
    return l > r ? T() : query(root_, l, r);
  }
};

vector<int> calcJumpSeq(const vector<int64_t>& height, const int64_t& d) {
  Index<int64_t> ix(height);
  MaxSegmentTree<pair<int, int>, FirstLess<int, int>> tree(ix.size());
  vector<int> pre(height.size());
  vector<int> jumps(height.size());
  for (int i = 0, n = static_cast<int>(height.size()); i < n; ++i) {
    pair<int, int> maxJump;
    pair<int, int> cand = tree.query(0, ix[height[i] - d + 1] - 1);
    maxJump = max(maxJump, cand);
    cand = tree.query(ix[height[i] + d], n - 1);
    maxJump = max(maxJump, cand);
    jumps[i] = maxJump.first + 1;
    pre[i] = maxJump.second;
    tree.insert(ix[height[i]], {jumps[i], i});
  }
  auto maxIt = max_element(jumps.begin(), jumps.end());
  vector<int> seq;
  for (int cur = maxIt - jumps.begin(); ; ) {
    seq.push_back(cur);
    if (jumps[cur] == 1) {
      break;
    }
    cur = pre[cur];
  }
  reverse(seq.begin(), seq.end());
  return seq;
}

int main() {
  ios::sync_with_stdio(false);
  int n;
  int64_t d;
  for (; cin >> n >> d; ) {
    vector<int64_t> height(n);
    for (auto& h : height) {
      cin >> h;
    }
    vector<int> seq = calcJumpSeq(height, d);
    cout << seq.size() << endl;
    for (size_t i = 0; i < seq.size(); ++i) {
      if (i > 0) {
        cout << " ";
      }
      cout << seq[i] + 1;
    }
    cout << endl;
  }
  return 0;
}
