class Solution {
public:
  bool canJump(int A[], int n) {
    // current furthest reachable position 
    int now = 0;
    for (int i = 0; i < n && now >= i; ++i) {
      now = std::max(now, i + A[i]);
    }
    return now >= n-1;
  }
};
