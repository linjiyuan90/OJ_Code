#include "vector"
#include "iostream"

// assume vt is not empty
int min_rotate_array(const std::vector<int> &vt) {
  int lo = 0, hi = vt.size() - 1;
  while (lo < hi) {
    int m = (lo + hi) / 2;
     if (vt[m] > vt[hi]) {
       lo = m+1;
     } else {
       hi = m;
     }
  }
  return vt[lo];
}

int main() {
  std::vector<int> vt;
  for (int i = 0; i < 6; ++i) {
    vt.push_back(i+1);
  }
  // rotate
  for (int i = 0; i < 6; ++i) {
    std::reverse(vt.begin(), --vt.end());
    std::reverse(vt.begin(), vt.end());
    std::cout << min_rotate_array(vt) << std::endl;
  }
  return 0;
}
