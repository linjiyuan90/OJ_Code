class Solution {
public:
  TreeNode *buildTree(std::vector<int> &inorder, std::vector<int> &postorder) {
    return buildTree(inorder.begin(),
		     inorder.end(), 
		     postorder.begin(), 
		     postorder.end());
  }
  
private:
  typedef std::vector<int>::const_iterator Iter;

  // Using iterator is more beautiful
  TreeNode *buildTree(Iter inorder_beg,
		      Iter inorder_end,
		      Iter postorder_beg,
		      Iter postorder_end) {
    if (inorder_beg >= inorder_end) {
      return NULL;
    }
    Iter root_it = postorder_end - 1;
    TreeNode *root = new TreeNode(*root_it);
    root_it = std::find(inorder_beg, inorder_end, *root_it);
    size_t left_size = root_it - inorder_beg;
    root->left = buildTree(inorder_beg,
			   root_it,
			   postorder_beg, 
			   postorder_beg + left_size);
    root->right = buildTree(root_it + 1,
			    inorder_end,
			    postorder_beg + left_size,
			    postorder_end - 1);
    return root;
  }
};
