#include "iostream"
#include "string"
#include "vector"
#include "queue"

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  std::vector<std::vector<int>> levelOrderBottom(TreeNode *root) {
    std::vector<std::vector<int>> ans;
    if (root == NULL) {
      return ans;
    }
    std::queue<TreeNode *> q[2];
    int now = 0, next = 1;
    q[now].push(root);
    while (!q[now].empty()) {
      ans.push_back(std::vector<int>());
      while (!q[now].empty()) {
	auto r = q[now].front();
	q[now].pop();
	ans.back().push_back(r->val);
	if (r->left != NULL) {
	  q[next].push(r->left);
	}
	if (r->right != NULL) {
	  q[next].push(r->right);
	}
      }
      std::swap(now, next);
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};

int main() {
  TreeNode *root = new TreeNode(3);
  TreeNode *r = new TreeNode(20);
  r->left = new TreeNode(15);
  r->right = new TreeNode(7);
  root->left = new TreeNode(9); 
  root->right = r;
  Solution sol;
  auto ans = sol.levelOrderBottom(root);
  for (auto l : ans) {
    std::cout << "[ ";
    for (auto e : l) {
      std::cout << e << " ";
    }
    std::cout << "]" << std::endl;
  }
  return 0;
}
