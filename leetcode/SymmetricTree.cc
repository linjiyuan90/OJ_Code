class Solution {
public:
  bool isSymmetric(TreeNode *root) {
    if (root == NULL) {
      return true;
    }
    return isSymmetric(root->left, root->right);
  }
  
private:
  bool isSymmetric(TreeNode *p, TreeNode *q) {
    if (p == NULL) {
      return q == NULL;
    }
    if (q == NULL) {
      return p == NULL;
    }
    return p->val == q->val &&
      isSymmetric(p->left, q->right) &&
      isSymmetric(p->right, q->left);
  }
};


// TODO
// do it iteratively
