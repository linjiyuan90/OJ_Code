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
public:
  vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
    vector<vector<int>> ans;
    if (root != NULL) {
      vector<TreeNode*> nodes[2];
      int now = 0, next = 1;
      nodes[now].push_back(root);
      for (int i = 0; !nodes[now].empty(); ++i) {
        nodes[next].clear();
        vector<int> nodeVals;
        for (TreeNode* p : nodes[now]) {
          nodeVals.push_back(p->val);
          if (p->left != NULL) {
            nodes[next].push_back(p->left);
          }
          if (p->right != NULL) {
            nodes[next].push_back(p->right);
          }
        }
        if (i & 1) {
          reverse(nodeVals.begin(), nodeVals.end());
        }
        ans.push_back(nodeVals);
        swap(now, next);
      }
    }
    return ans;
  }
};
