#ifndef BINARY_SEARCH_TREE_H__
#define BINARY_SEARCH_TREE_H__

#include "BinaryTree.h"

template<typename T>
class BinarySearchTree : public BinaryTree<T> {
 public:
  using BinarySearchTreePtr = std::shared_ptr<BinarySearchTree>;
  
  //  BinaryTreePtr or BinarySearchTreePtr?
 BinarySearchTree(T data,
                  BinarySearchTreePtr left = nullptr,
                  BinarySearchTreePtr right = nullptr):
  BinaryTree<T>(data, left, right) {
  }
};

template<typename T>
using BinarySearchTreePtr = typename BinarySearchTree<T>::BinarySearchTreePtr;


#endif // BINARY_SEARCH_TREE_H__
