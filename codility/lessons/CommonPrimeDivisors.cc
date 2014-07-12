// check whether a, b has same prime factors
// just check (a/g, g) and (b/g, g)
// divide g until g = 1
// Since each divison remove some common factors

int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);    
}

bool no_other_factors(int x, int g) {
  if (g == 1) {
    return x == 1;
  }
  g = gcd(x, g);
  return no_other_factors(x/g, g);
}

int solution(vector<int> &A, vector<int> &B) {
  int cnt = 0;
  for (int i = 0, n = A.size(); i < n; ++i) {
    int a = A[i], b = B[i];
    int g = gcd(a, b);
    if (no_other_factors(a/g, g) && no_other_factors(b/g, g)) {
      ++ cnt;
    }
  }
  return cnt;
}
