class Solution {
public:
  TreeNode *sortedArrayToBST(std::vector<int> &num) {
    return build_BST(num, 0, num.size() - 1);
  }
private:
  TreeNode *build_BST(std::vector<int> &num, int left, int right) {
    if (left > right) {
      return NULL;
    }
    int mid = (left + right) / 2;
    TreeNode *root = new TreeNode(num[mid]);
    root->left = build_BST(num, left, mid - 1);
    root->right = build_BST(num, mid+1, right);
    return root;
  }
};
