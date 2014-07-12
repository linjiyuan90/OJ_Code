int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);    
}

int solution(int N, int M) {
  return N / gcd(N, M);
}
