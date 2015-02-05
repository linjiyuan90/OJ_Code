class Solution {
public:
  vector<int> grayCode(int n) {
    // code[i] and code[i+1] has only one difference
    // suppose we have code[0..2^k), to build code[2^k, 2^(k+1))
    // append '0' to code[0..2^k), then append '1' to code(2^k..0]
    // 0 xxx1
    // 0 xxx2
    // 1 xxx2
    // 1 xxx1
    std::vector<int> code(1<<n);
    code[0] = 0;
    code[1] = 1;
    for (int l = 2; l <= n; ++l) {
      // append '0', done :)
      // append '1'
      int half = 1 << (l-1);
      int all = 1 << l;
      for (int i = half; i < all; ++i) {
        code[i] = half + code[all-i-1];
      }
    }
    return code;
  }
};
