/*
  Find a subtree with max sum in a unrooted tree.
  No recursive solution.
 */
#include "map"
#include "iostream"
#include "vector"
#include "memory"

class TreeNode {
public:
  typedef std::shared_ptr<TreeNode> TreeNode_ptr;
  int val;  
  std::vector<TreeNode_ptr> children;

  TreeNode(int val): val(val) {}
  void add(const TreeNode_ptr& ch) {
    children.push_back(ch);
  }
};

using TreeNode_ptr =  TreeNode::TreeNode_ptr;

int maxsum_subtree(const TreeNode_ptr& root) {
  std::vector<TreeNode_ptr> queue;
  std::map<TreeNode_ptr, int> dp;
  queue.push_back(root);
  for (size_t beg = 0, end = queue.size(); 
       beg != end; 
       ++beg, end = queue.size()) {
    auto& now = queue[beg];
    for(auto& ch : now->children) {
      queue.push_back(ch);
    }
  }
  int res = 0;
  for (auto it = queue.rbegin(); it != queue.rend(); ++it) {
    auto now = *it;
    dp[now] = now->val;
    for (auto& ch : now->children) {
      if (dp[ch] > 0) {
	dp[now] += dp[ch];
      }
    }
    res = std::max(res, dp[now]);
  }
  return res;
}

int main() {
  std::shared_ptr<TreeNode> root {new TreeNode(1)};
  root->add(std::make_shared<TreeNode>(-2));
  root->add(std::make_shared<TreeNode>(3));
  root->add(std::make_shared<TreeNode>(0));
  root->children[0]->add(std::make_shared<TreeNode>(-1));
  root->children[1]->add(std::make_shared<TreeNode>(-5));
  root->children[1]->children[0]->add(std::make_shared<TreeNode>(6));
  root->children[1]->children[0]->children[0]->add(std::make_shared<TreeNode>(-2));
  root->children[2]->add(std::make_shared<TreeNode>(4));
  std::cout << maxsum_subtree(root) << std::endl;
  return 0;
}
