
int solution(int n) {
  int res = 1;
  for (int i = 2; i <= n/i; ++i) {
    int c = 0;
    while(n % i == 0) {
      n /= i;
    }
    res *= (1 + c);
  }
  if (n > 1) {
    res *= 2;
  }
  return res;
}
