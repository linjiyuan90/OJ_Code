#include "iostream"
#include "vector"

typedef std::vector<int>::iterator Iter;

Iter partition(Iter beg, Iter end, int v) {
  Iter left = beg, right = end;
  for (; beg < right;) {
    if (*beg < v) {
      std::swap(*left++, *beg++);
    } else if (*beg > v) {
      std::swap(*--right, *beg);
    } else {
      ++ beg;
    }
  }
  return left;
}

// k starts from 0
int findKth(Iter beg, Iter end, int k) {
  Iter mid = partition(beg, end, *beg);
  int m = mid - beg;
  if (k == m) {
    return *mid;
  } else if (k < m) {
    return findKth(beg, mid, k);        
  } else {
    return findKth(mid + 1, end, k - m - 1);
  }
}

int main() {
  for (int n; std::cin >> n;) {
    std::vector<int> arr(n);
    for (auto& e : arr) {
      std::cin >> e;
    }
    std::cout << findKth(arr.begin(), arr.end(), n / 2) << std::endl;
  }
}
