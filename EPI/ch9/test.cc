
#include "cassert"

#include "iostream"
#include "vector"
#include "string"
#include "type_traits"

#include "BinaryTree.h"
#include "BinaryTreeWithParent.h"

void test_binarytree() {
  /*
        1
      2   3
       4 5
      6   7
           8
   */
  std::vector<BinaryTreePtr<int>> nodes(9);
  for (int i = 1; i <= 8; ++i) {
    nodes[i].reset(new BinaryTree<int>(i));
  }
  nodes[1]->left = nodes[2];
  nodes[1]->right = nodes[3];
  nodes[2]->right = nodes[4];
  nodes[4]->left = nodes[6];
  nodes[3]->left = nodes[5];
  nodes[5]->right = nodes[7];
  nodes[7]->right = nodes[8];
  BinaryTreePtr<int> root = nodes[1];

  // traversal
  // 1 2 4 6 3 5 7 8
  auto preorders = preorder_traversal<int>(root);
  assert(preorders == (decltype(preorders){
        nodes[1], nodes[2], nodes[4], nodes[6], nodes[3], nodes[5], nodes[7], nodes[8]
          }));
  // 2 6 4 1 5 7 8 3
  auto inorders = inorder_traversal<int>(root);
  assert(inorders == (decltype(inorders){
        nodes[2], nodes[6], nodes[4], nodes[1], nodes[5], nodes[7], nodes[8], nodes[3]
          }));
  // 6 4 2 8 7 5 3 1
  auto postorders = postorder_traversal<int>(root);
  assert(postorders == (decltype(postorders){
        nodes[6], nodes[4], nodes[2], nodes[8], nodes[7], nodes[5], nodes[3], nodes[1]
          }));

  assert(is_balanced<int>(root) == false);

  assert(is_symmetric<int>(root) == false);
  root->left = BinaryTreePtr<int>(new BinaryTree<int>(2, nullptr, BinaryTreePtr<int>(new BinaryTree<int>(3, BinaryTreePtr<int>(new BinaryTree<int>(4))))));
  root->right = BinaryTreePtr<int>(new BinaryTree<int>(2, BinaryTreePtr<int>(new BinaryTree<int>(3, nullptr, BinaryTreePtr<int>(new BinaryTree<int>(4))))));
  assert(is_symmetric<int>(root) == true);
}

void test_binarytreeWithParent() {
  /*
         3
       2   4
     1   5   7
           6 
         8
  */
  BinaryTreeWithParentPtr<int> root(new BinaryTreeWithParent<int>(3));
  root->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(2, nullptr, nullptr, root));
  root->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(4, nullptr, nullptr, root));
  root->left->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(1, nullptr, nullptr, root->left));
  root->right->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(5, nullptr, nullptr, root->right));
  root->right->left->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(6, nullptr, nullptr, root->right->left));
  root->right->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(7, nullptr, nullptr, root->right));
  root->right->left->right->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(8, nullptr, nullptr, root->right->left->right));
  
  assert((inorder_traversal<int>(root)) == (iterative_inorder_traversal<int>(root)));

  root =  BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(1));
  root->left =  BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(2, nullptr, nullptr, root));
  assert((inorder_traversal<int>(root)) == (iterative_inorder_traversal<int>(root)));

  /*
      1
    2   4
      3   5
    6
     7
   */
  root =  BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(1));
  root->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(2, nullptr, nullptr, root));
  root->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(4, nullptr, nullptr, root));
  root->left->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(3, nullptr, nullptr, root->left));
  root->right->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(5, nullptr, nullptr, root->right));
  root->left->right->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(6, nullptr, nullptr, root->left->right));
  root->left->right->left->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(6, nullptr, nullptr, root->left->right->left));
  assert((inorder_traversal<int>(root)) == (iterative_inorder_traversal<int>(root)));

  /*
        1
      2
    3
   4
  */
  root =  BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(1));
  root->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(2, nullptr, nullptr, root));
  root->left->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(3, nullptr, nullptr, root->left));
  root->left->left->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(4, nullptr, nullptr, root->left->left));
  assert((inorder_traversal<int>(root)) == (iterative_inorder_traversal<int>(root)));

  /*
       1
    2    4
       3   5
        6 7
     
   */
  root =  BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(1));
  root->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(2, nullptr, nullptr, root));
  root->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(4, nullptr, nullptr, root));
  root->right->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(3, nullptr, nullptr, root->right));
  root->right->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(5, nullptr, nullptr, root->right));
  root->right->left->right = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(6, nullptr, nullptr, root->right->left));
  root->right->right->left = BinaryTreeWithParentPtr<int>(new BinaryTreeWithParent<int>(7, nullptr, nullptr, root->right->right));
  assert((inorder_traversal<int>(root)) == (iterative_inorder_traversal<int>(root)));

}

int main() {
  test_binarytree();
  test_binarytreeWithParent();
}
