class Solution {
public:
  int reverse(int x) {
    int rx = 0;
    while (x != 0) {
      rx = rx * 10 + x % 10;
      x /= 10;
    }
    return rx;
  }
};
