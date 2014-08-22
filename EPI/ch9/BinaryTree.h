#ifndef BINARY_TREE_H__
#define BINARY_TREE_H__

#include "algorithm"
#include "memory"

template<typename T>
class BinaryTree {
 public:
  using BinaryTreePtr = std::shared_ptr<BinaryTree<T>>;

  T data;
  BinaryTreePtr left, right;
  
  BinaryTree(T data,
             BinaryTreePtr left = nullptr,
             BinaryTreePtr right = nullptr);
  
};

template<typename T>
using BinaryTreePtr = typename BinaryTree<T>::BinaryTreePtr;

template<typename T>
BinaryTree<T>::BinaryTree(T data,
                          BinaryTreePtr left,
                          BinaryTreePtr right):
data(data), left(left), right(right) {
}

template<typename T>
std::pair<bool, int> is_balanced_with_height(BinaryTreePtr<T> root) {
  if (!root) {
    return {true, 0};
  }
  auto left = is_balanced_with_height<T>(root->left);
  auto right = is_balanced_with_height<T>(root->right);
  return {left.first && right.first && ::abs(left.second - right.second) <= 1,
      std::max(left.second, right.second) + 1};
}

template<typename T>
bool is_balanced(BinaryTreePtr<T> root) {
  return is_balanced_with_height<T>(root).first;
}


// outside the scope needs <T>

// If the tree is mutable, Morris Traversal with O(1) space
template<typename T>
std::vector<BinaryTreePtr<T>> preorder_traversal(BinaryTreePtr<T> root) {
  std::vector<BinaryTreePtr<T>> orders;
  while (root) {
    if (root->left) {
      BinaryTreePtr<T> p = root->left;
      while (p->right && p->right != root) {
        p = p->right;
      }
      if (p->right) {
        p->right = nullptr;
        root = root->right;
      } else {
        orders.push_back(root);  // only change here
        p->right = root;
        root = root->left;
      }
    } else {
      orders.push_back(root);
      root = root->right;
    }
  }
  return orders;
}

template<typename T>
std::vector<BinaryTreePtr<T>> inorder_traversal(BinaryTreePtr<T> root) {
  std::vector<BinaryTreePtr<T>> orders;
  while (root) {
    if (root->left) {
      BinaryTreePtr<T> p = root->left;
      while (p->right && p->right != root) {
        p = p->right;
      }
      if (p->right) {
        orders.push_back(root);
        p->right = nullptr;
        root = root->right;
      } else {
        p->right = root;
        root = root->left;
      }
    } else {
      orders.push_back(root);
      root = root->right;
    }
  }
  return orders;
}

template<typename T>
std::vector<BinaryTreePtr<T>> postorder_traversal(BinaryTreePtr<T> root) {
  // traverse according to: root right left
  // then reverse
  std::vector<BinaryTreePtr<T>> orders;
  while (root) {
    if (root->right) {
      BinaryTreePtr<T> p = root->right;
      while (p->left && p->left != root) {
        p = p->left;
      }
      if (p->left) {
        p->left = nullptr;
        root = root->left;
      } else {
        orders.push_back(root);
        p->left = root;
        root = root->right;
      }
    } else {
      orders.push_back(root);
      root = root->left;
    }
  }
  std::reverse(orders.begin(), orders.end());
  return orders;
}

template<typename T>
bool is_symmetric(const BinaryTreePtr<T>& left, const BinaryTreePtr<T>& right) {
  if (!left && !right) {
    return true;
  }
  if (!left || !right) {
    return false;
  }
  return left->data == right->data 
    && is_symmetric<T>(left->left, right->right)
    && is_symmetric<T>(left->right, right->left);
}

template<typename T>
bool is_symmetric(const BinaryTreePtr<T>& root) {
  return (!root || is_symmetric<T>(root->left, root->right));
}

template<typename T>
BinaryTreePtr<T> kth_node(BinaryTreePtr<T> root) {
  
}

// full binary tree
// complete binary tree
// perfect binary tree

#endif // BINARY_TREE_H__
