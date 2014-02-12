class Solution {
public:
  std::vector<int> grayCode(int n) {
    // construct n gray from n-1 gray
    // note when n = 0, code = {0}
    std::vector<int> code{0};
    code.reserve(1<<n);
    // if not reserved, the following code is dangerous since the iterator may
    // be illegal when code is increasing!!!
    // Using index could be safer!
    for (int k = 1; k <= n; ++k) {
      std::transform(code.rbegin(),
		     code.rend(),
		     std::back_inserter(code),
		     [k](int x) {
		       return x + (1<<k-1);
		     });
    }
    return code;
  }
};
