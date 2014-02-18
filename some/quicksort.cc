#include "iostream"
#include "vector"
#include "algorithm"
#include "cassert"

// <p, =p, >p
std::vector<int>::iterator partition(std::vector<int>::iterator beg,
				     std::vector<int>::iterator end) {
  int p = *beg;
  std::vector<int>::iterator it = beg, jt = beg, kt = end;
  for (it = beg, jt = beg, kt = end; jt < kt;) {
    if (*jt < p) {
      std::swap(*it++, *jt);
    } else if (*jt > p) {
      std::swap(*(--kt), *jt);
    } else {
      ++ jt;
    }
  }
  return it;
}

void sort(std::vector<int>::iterator beg,
	  std::vector<int>::iterator end) {
  if (beg + 1 >= end) {
    return;
  }
  auto mit = partition(beg, end);
  sort(beg, mit);
  sort(mit + 1, end); // note mit + 1, the pivot is already ok
}

int partition(std::vector<int> &vt, int p) {
  int n = vt.size();
  // int p = vt[0];
  int i, j, k;
  for (i = 0, j = 0, k = n; j < k;) {
    if (vt[j] < p) {
      std::swap(vt[i++], vt[j++]);
    } else if (vt[j] > p) {
      std::swap(vt[--k], vt[j]);
    } else {
      ++j;
    }
  }
  return i;
}

int main() {
  
  std::vector<int> vt{20, 3, 1, 3, 0, -1, 5, 10, 0};
  sort(vt.begin(), vt.end());
  for (int n = 1; n <= 10; ++n) {
    std::vector<int> vt;
    for (int i = 0; i < n; ++i) {
      vt.push_back(i);
    }
    do {
      std::vector<int> vt1 = vt;
      sort(vt1.begin(), vt1.end());
      std::vector<int> vt2 = vt;
      std::sort(vt2.begin(), vt2.end());
      assert(vt1 == vt2);
    } while(std::next_permutation(vt.begin(), vt.end()));
    std::cout << "ok" << std::endl;
  }
  return 0;
}
