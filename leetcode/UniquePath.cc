class Solution {
public:
  int uniquePaths(int m, int n) {
    --m;
    --n;
    // totally m+n steps, choose n right steps
    // C(m+n, m) = (n+m)!/n!m! = (n+1)*...(n+m)/m!
    long long dividend = 1, divisor = 1;
    for (int i = n+1; i <= n+m; ++i) {
      divisor *= i-n;
      dividend *= i;
      long long g = gcd(divisor, dividend);
      divisor /= g;
      dividend /= g;
    }
    return dividend / divisor;
  }

private:
  long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
  }
};


// Another approach
// dp[0][0] = 1
// dp[i][j] = dp[i-1][j] + dp[i][j-1]
