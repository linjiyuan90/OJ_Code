#include "queue"
#include "algorithm"

struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(int x): val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
  // recursive solution
  // https://github.com/Dionysus1227/edocteel/blob/master/Populating%20Next%20Right%20Pointers%20in%20Each%20Node%20II.cc
  void connect(TreeLinkNode *root) {
    if (root == NULL) {
      return;
    }
    TreeLinkNode *next_root = NULL, *prev = NULL;
    for (root; root != NULL; root = root->next) {
      update(prev, root->left, next_root);
      update(prev, root->right, next_root);
    }
    connect(next_root);
  }

private:
  void update(TreeLinkNode *&prev, TreeLinkNode *&cur, TreeLinkNode *&next_root) {
    if (cur == NULL) {
      return;
    }
    if (next_root == NULL) {
      prev = next_root = cur;
      return;
    }
    prev->next = cur;
    prev = cur;
  }

  // non recursive
  void connect2(TreeLinkNode *root) {
    if (root == NULL) {
      return;
    }
    // use two queues to split levels
    std::queue<TreeLinkNode *> q[2];
    int now = 0, next = 1;
    q[now].push(root);
    while (!q[now].empty()) {
      TreeLinkNode *last = NULL, *cur;
      while (!q[now].empty()) {
	cur = q[now].front();
	q[now].pop();
	if (last != NULL) {
	  last->next = cur;
	}
	if (cur->left != NULL) {
	  q[next].push(cur->left);
	}
	if (cur->right != NULL) {
	  q[next].push(cur->right);
	}
	last = cur;
      }
      std::swap(now, next);
    }
  }

};
