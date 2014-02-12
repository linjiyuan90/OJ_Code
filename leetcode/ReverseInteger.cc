class Solution {
public:
  // what about overflow?
  int reverse(int x) {
    // no need to consider negative independently!
    int ans = 0;
    while (x != 0) {
      ans = ans * 10 + x % 10;
      x /= 10;
    }
    return ans;
  }
};
