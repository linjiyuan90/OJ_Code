#include "memory"
#include "vector"

class TreeNode {
public:
  typedef std::unique_ptr<TreeNode*> TreeNodePtr;

  TreeNode(int id): id(id) {
  }    

private:
  int id;
  std::vector<TreeNodePtr> children;
};

using TreeNodePtr = TreeNode::TreeNodePtr;


