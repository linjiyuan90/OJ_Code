
# 11.10 Search in a 2D array where rows and columns are increasing
Start from A[0][n-1], at each time choose to ++r, or --c. At most 2n-1 steps.
```c++
template <typename T>
bool matrix_search(const std::vector<std::vector<T>> &A, const T &x) {
  int r = 0, c = A[0].size() - 1;
  while (r < A.size() && c >= 0) {
    if (A[r][c] == x) {
      return true;
    } else if (A[r][c] < x) {
      ++r;
    } else {
      --c;
    }
  }
  return false;
}
```

# 11.13 kth element, or first kth elements, O(n)
```c++
template <typename T>
int partition(std::vector<T> &A, const int &l, const int &r) {
  std::default_random_engine gen((std::random_device())());
  std::uniform_int_distribution<int> dis(l, r);
  const T pivot = A[dis(gen)];
  int gt = l, lt = r + 1;
  for (int i = l; i < lt;) {
    if (A[i] > pivot) {
      std::swap(A[gt++], A[i++]);
    } else if (A[i] < pivot) {
      std::swap(A[i], A[--lt]);
    } else {
      ++ i;
    }
  }
  return lt - 1;
}
template <typename T>
T find_kth_largest(std::vector<T> &A, const int &k) {
  int l = 0, r = A.size() - 1;
  // iterative seems better than recursive
  while (l <= r) {
    int p = partition(A, l, r);
    // now, A[l..p] >= A[p]
    if (p == k - 1) {
      return A[p];
    } else if (p > k - 1) {
      r = p - 1;
    } else {
      l = p + 1;
    }
  }
}
// nth_element(A.begin(), A.begin() + k, A.end(), std::greater<T>());
```
After `quick selection`, the first k elements in the result array is the first k largest ones.

# 11.14 First k largest element while n is unknown, O(n) time, O(k) space

Maintaining a min_heap will solve this problem in O(nlogk). The O(n) solution is to maintain an array with size 2k-1. Each time, when the array size reach 2k-1, select the first k largest using `quick selection`, then remove the remaining k-1 elements. In fact, this solution looks like the one with heap!
```c++
template <typename T>
T find_k_th_largest_unknown_length(std::istringstream &sin, const int &k) {
  std::vector<T> M;
  T x;
  while (sin >> x) {
    M.emplace_back(x);
    if (M.size() == 2*k - 1) {
      // Keep the k largest elements and discard the small ones
      std::nth_element(M.begin(), M.begin() + k - 1, M.end(), std::greater<T>());
      M.resize(k);
    }
  }
  std::nth_element(M.begin(), M.begin() + k - 1, M.end(), std::greater<T>());
  return M[k-1];
}
```
