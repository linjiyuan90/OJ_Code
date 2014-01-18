#include "iostream"
#include "algorithm"
#include "stack"

class Solution {
public:
  int trap(int A[], int n) {
    int ans = 0;
    // maintain a monotonically decreasing stack
    std::stack<int> desc_walls;
    for (int i = 0; i < n; ++i) {
      while (desc_walls.size() > 1 && A[desc_walls.top()] <= A[i]) {
	int h = A[desc_walls.top()];
	desc_walls.pop();
	ans += (std::min(A[i], A[desc_walls.top()]) - h) * (i - desc_walls.top() - 1);
      }
      if (!desc_walls.empty() && A[desc_walls.top()] <= A[i]) {
	desc_walls.pop();
      }
      desc_walls.push(i);
    }
    return ans;
  }
};

// [4, 2, 3] 1
// [2, 0, 2] 2
// [0,1,0,2,1,0,1,3,2,1,2,1] 6

int main() {
  int A[] = {0,1,0,2,1,0,1,3,2,1,2,1};
  Solution sol;
  std::cout << sol.trap(A, 12) << std::endl;
  return 0;
}
