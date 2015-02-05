
class Solution {
  const std::string Digits = "123456789";
  std::vector<int> factorial;

public:
  Solution() {
    factorial.resize(10);
    std::iota(factorial.begin(), factorial.end(), 0);
    factorial[0] = 1;
    std::partial_sum(factorial.begin(), factorial.end(), factorial.begin(), std::multiplies<int>());
  }

  std::string getPermutation(int n, int k) {
    --k; // k starts from 0
    std::string all_digits = Digits.substr(0, n);
    std::string ans;
    for (int i = n - 1; i >= 0; --i) {
      int d = k/factorial[i];
      ans += all_digits[d];
      k %= factorial[i];
      // need to use iterator rather than index
      all_digits.erase(all_digits.begin() + d);
    }
    return ans;
  }
};
