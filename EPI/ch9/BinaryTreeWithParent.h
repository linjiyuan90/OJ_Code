#ifndef BINARY_TREE_WITH_PARENT_H
#define BINARY_TREE_WITH_PARENT_H

#include "BinaryTree.h"

template<typename T>
class BinaryTreeWithParent: public BinaryTree<T> {
 public:

  using BinaryTreeWithParentPtr = std::shared_ptr<BinaryTreeWithParent<T>>;

 BinaryTreeWithParent(T data, 
                      BinaryTreePtr<T> left = nullptr,
                      BinaryTreePtr<T> right = nullptr, 
                      BinaryTreePtr<T> parent = nullptr): 
  BinaryTree<T>(data, left, right), parent(parent) { }

  BinaryTreePtr<T> parent;
};

template<typename T>
using BinaryTreeWithParentPtr = typename BinaryTreeWithParent<T>::BinaryTreeWithParentPtr;

template<typename T>
std::vector<BinaryTreePtr<T>> iterative_inorder_traversal(const BinaryTreeWithParentPtr<T>& root) {
  std::vector<BinaryTreePtr<T>> order;
  for (BinaryTreePtr<T> pre = nullptr, cur = root; cur != nullptr; ) {
    if (pre != nullptr && cur->right == pre) {
      pre = cur;
      BinaryTreeWithParentPtr<T> _cur = std::static_pointer_cast<BinaryTreeWithParent<T>>(cur);
      cur = _cur->parent;    
    } else if (!cur->left || cur->left == pre) {
      order.push_back(cur);
      pre = cur;
      if (cur->right) {
        cur = cur->right;
      } else {
        BinaryTreeWithParentPtr<T> _cur = std::static_pointer_cast<BinaryTreeWithParent<T>>(cur);
        cur = _cur->parent;
      }
    } else {
      pre = cur;
      cur = cur->left;
    }
  }
  return order;
}

#endif // BINARY_TREE_WITH_PARENT_H
