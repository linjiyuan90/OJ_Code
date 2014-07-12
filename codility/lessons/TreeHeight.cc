#include "iostream"
#include "algorithm"

struct tree {
  int x;
  tree *l;
  tree *r;
};

int solution(tree *T) {
  if (T == NULL) {
    return -1;
  }
  int h = 0;
  if (T->l != NULL) {
    h = std::max(h, solution(T->l) + 1);
  }
  if (T->r != NULL) {
    h = std::max(h, solution(T->r) + 1);
  }
  return h;
}

