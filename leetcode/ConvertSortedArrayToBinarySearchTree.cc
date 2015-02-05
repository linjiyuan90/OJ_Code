/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  typedef std::vector<int>::iterator Iter;
    
  TreeNode* sortedArrayToBST(Iter beg, Iter end) {
    if (end == beg) {
      return NULL;
    }
    Iter mid = beg + std::distance(beg, end)/2;
    TreeNode* root = new TreeNode(*mid);
    root->left = sortedArrayToBST(beg, mid);
    root->right = sortedArrayToBST(mid+1, end);
    return root;
  }
    
public:
  TreeNode* sortedArrayToBST(vector<int>& num) {
    return sortedArrayToBST(num.begin(), num.end());
  }
};
