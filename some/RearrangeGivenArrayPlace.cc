// http://www.geeksforgeeks.org/rearrange-given-array-place/
// Rearrange an array so that arr[i] becomes arr[arr[i]] with
// O(1) extra place

// DO NOT connect it with cycle! (when to use cycle?)
// Store both arr[i] and arr[arr[i]] in arr[i] simultaneously
// arr[i] += (arr[arr[i]] % n) * n

#include "iostream"
#include "vector"

void rerange(std::vector<int> &arr) {
  int n = arr.size();
  for (int i = 0; i < n; ++i) {
    arr[i] += (arr[arr[i]] % n) * n;
  }
  for (int i = 0; i < n; ++i) {
    arr[i] /= n;
  }
}

int main() {
  for (auto arr : std::vector<std::vector<int>>{
      {3, 2, 0, 1}, {4, 0, 2, 1, 3}, {0, 1, 2, 3}
    }) {
    rerange(arr);
    for (auto e : arr) {
      std::cout << e << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
