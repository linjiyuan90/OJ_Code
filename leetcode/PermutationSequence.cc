
// Calling nextPermutation is slow
class Solution {
public:
  std::string getPermutation(int n, int k) {
    std::string s = std::string("123456789").substr(0, n);
    std::string ans = "";
    --k;
    // a1*(n-1)! + a2*(n-2)! + an-1*1!
    int f = factorial(n);
    for (int i = n; i > 0; --i) {
      f /= i;
      int j = k/f; // nicer than while and substract
      k -= j*f;
      ans += s[j];
      s.erase(s.begin() + j);
    }
    return ans;
  }
  
private:
  int factorial(int n) {
    int f = 1;
    for (int i = 1; i <= n; ++i) {
      f *= i;
    }
    return f;
  }
};
