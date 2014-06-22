
#include "iostream"
#include "memory"

template<typename T>
class BinaryTree {
 public:
  T data;
  std::shared_ptr<BinaryTree<T>> left, right;
};

// Morris Traversal
template<typename T>
void inorder_traversal(std::shared_ptr<BinaryTree<T>> root) {
  while(root) {
    if (root->left) {
      // Find the predecessor of root
      std::shared_ptr<BinaryTree<T>> p = root->left;
      while (p->right != root && p->right != nullptr) {
	p = p->right;
      }
      // Build the successor link
      if (p->right == nullptr) {
	p->right = root;
	root = root->left;
      } else {
	// Revert the successor link if predecessor's successor is root
	p->right = nullptr;
	std::cout << root->data << std::endl;
	root = root->right;
      }
    } else {
      std::cout << root->data << std::endl;
      root = root->right;
    }
  }
}

// How to write iterative postorder?

// Build tree from array/list?
template<typename T>
BinaryTree<T> build_tree(size_t n) {
  std::vector<T> num(n);
  for (int i = 0; i < n; ++i) {
    num[i] = i;
  }
  return build_tree(num.cbegin(), num.cend());
}

// how to typedef?
template<typename T, 
	 typedef std::vector<T>::const_iterator CIT>
BinaryTree<T> build_tree() {
  
}

void inorder_traversal_test() {
  BinaryTree<int> bt;
  
}

int main() {
  
  return 0;
}
