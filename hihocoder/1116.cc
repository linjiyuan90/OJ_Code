#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int Mod = 10007;
const int MaxN = 100000;

struct SegmentTreeNode {
  int left, right, product, leftProductSum, rightProductSum;
  SegmentTreeNode *leftNode, *rightNode;
  SegmentTreeNode() {}
  SegmentTreeNode(int left, int right,
                  SegmentTreeNode* leftNode = NULL,
                  SegmentTreeNode* rightNode = NULL) :
    left(left), right(right), product(0), leftProductSum(0), rightProductSum(0),
    leftNode(leftNode), rightNode(rightNode) {
  }
};

/*
  ProductSegmentTree has responsibilities of maintaining the following values of val[i..j]:
  1) product = val[i] * val[i+1] * ... * val[j]
  2) leftProductSum = val[j] +
                      val[j] * val[j-1] +
                      val[j] * val[j-1] * val[j-2] +
                      ... 
                      val[j] * val[j-1] * ... * val[i]
  3) rightProductSum, similar to leftProductSum

  the update is single point update
*/
class ProductSegmentTree {
  int n;
  SegmentTreeNode* root;

  SegmentTreeNode* build(int i, int j) {
    SegmentTreeNode* root = new SegmentTreeNode(i, j);
    if (i == j) {
      return root;
    }
    int mid = (i+j)/2;
    root->leftNode = build(i, mid);
    root->rightNode = build(mid+1, j);
    return root;
  }
  
  void update(SegmentTreeNode* root, int i, int x) {
    if (i < root->left || i > root->right) {
      return;
    }
    if (root->left == root->right) {
      root->product = root->leftProductSum = root->rightProductSum = x % Mod;
      return;
    }
    SegmentTreeNode* leftNode = root->leftNode;
    SegmentTreeNode* rightNode = root->rightNode;
    update(leftNode, i, x);
    update(rightNode, i, x);    
    root->product = leftNode->product * rightNode->product % Mod;
    root->leftProductSum = (leftNode->leftProductSum * rightNode->product + rightNode->leftProductSum) % Mod;
    root->rightProductSum = (rightNode->rightProductSum * leftNode->product + leftNode->rightProductSum) % Mod;
  }

  // return {leftProductSum or rightProductSum, product} of val[i..j]
  pair<int, int> query(SegmentTreeNode* root, int i, int j, bool isLeft) {
    if (j < root->left || i > root->right) {
      return make_pair(0, 1);
    }
    if (i <= root->left && root->right <= j) {
      return make_pair(isLeft ? root->leftProductSum : root->rightProductSum, root->product);
    }
    int mid = (root->left + root->right) / 2;
    pair<int, int> l = query(root->leftNode, i, j, isLeft);
    pair<int, int> r = query(root->rightNode, i, j, isLeft);
    if (!isLeft) {
      swap(l, r);
    }
    int productSum = (l.first * r.second + r.first) % Mod;
    return make_pair(productSum, l.second * r.second % Mod);
  }

public:
  
  ProductSegmentTree(int n) : n(n), root(build(1, n)) {
  }
  
  void update(int i, int x) {
    update(root, i, x);
  }

  // return {leftProductSum[1..i-1], rightProductSum[i+1, n]}
  pair<int, int> query(int i) {
    pair<int, int> l = query(root, 1, i-1, true);
    pair<int, int> r = query(root, i+1, n, false);
    return make_pair(l.first, r.first);
  }
};

int main() {
  ios::sync_with_stdio(false);
  vector<int> a;
  for (int n, q; cin >> n >> q; ) {
    a.assign(n, 0);
    ProductSegmentTree tree(n);
    int sum = 0;
    for (int i = 0, x, y; i < q; ++i) {
      cin >> x >> y;
      pair<int, int> p = tree.query(x);
      sum = (sum + (y - a[x-1]) * (p.first + 1) % Mod * (p.second + 1) % Mod + Mod) % Mod;
      // cout is quite slow --!
      // cout << sum << endl;
      printf("%d\n", sum);
      tree.update(x, y);
      a[x-1] = y;
    }
  }
  return 0;
}

