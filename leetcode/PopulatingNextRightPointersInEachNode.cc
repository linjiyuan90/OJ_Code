class Solution {
public:
  void connect(TreeLinkNode *root) {
    for (TreeLinkNode *beg = root; beg != NULL; ) {
      TreeLinkNode *next = NULL;
      for (TreeLinkNode *prev = NULL, *cur = beg; cur != NULL;
	   cur = cur->next) {
	update(next, prev, cur->left);
	update(next, prev, cur->right);
      }
      beg = next;
    }
  }

private:
  void update(TreeLinkNode *&next, TreeLinkNode *&prev, TreeLinkNode *cur) {
    if (cur == NULL) {
      return;
    }
    if (next == NULL) {
      next = cur;
    }
    if (prev != NULL) {
      prev->next = cur;
    }
    prev = cur;
  }
};
