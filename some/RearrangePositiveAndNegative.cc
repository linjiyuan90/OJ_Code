#include "vector"
#include "iostream"

// http://www.geeksforgeeks.org/rearrange-positive-and-negative-numbers-publish/
// rearrange to make postivite and negative are placed alternatively.

void print(const std::vector<int> &vt) {
  for (auto e : vt) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

void rearrange(std::vector<int> &vt) {
  // first partition
  int n = vt.size();
  int i, j;
  for (i = 0, j = 0; j < n; ++j) {
    if (vt[j] > 0) {
      std::swap(vt[i++], vt[j]);
    }
  }

  // print(vt);
    
  // now, there are i positive numbers
  // rearrange one-by-one
  for (j = i, i = 0; i < n && vt[i] > 0 && i + 1 < n && j < n; ++j) {
    if (vt[i+1] < 0) {
      break;
    }
    std::swap(vt[i+1], vt[j]);
    i += 2;
  }
}

int main() {
  // test four situation
  for (auto vt : std::vector<std::vector<int>> {
      {-1, 1, -2, 2}, {-1, 1, -2, 2, -3},
			{-1, 1, -2, 2, 3}, {-1, 1, -2, -3, -4}
    }) {
    rearrange(vt);
    print(vt);
  }
  return 0;
}
