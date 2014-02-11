class Solution {
public:
  TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder) {
    return buildTree(preorder.begin(),
		     preorder.end(),
		     inorder.begin(),
		     inorder.end());
  }

private:
  typedef std::vector<int>::const_iterator Iter;
  
  TreeNode *buildTree(Iter preorder_beg,
		      Iter preorder_end,
		      Iter inorder_beg,
		      Iter inorder_end) {
    if (preorder_beg >= preorder_end) {
      return NULL;
    }
    Iter root_it = std::find(inorder_beg, inorder_end, *preorder_beg);
    size_t left_size = root_it - inorder_beg;
    TreeNode *root = new TreeNode(*root_it);
    root->left = buildTree(preorder_beg + 1,
			   preorder_beg + 1 + left_size,
			   inorder_beg,
			   root_it);
    root->right = buildTree(preorder_beg + 1 + left_size,
			    preorder_end,
			    root_it + 1,
			    inorder_end);
    return root;
  }
};
