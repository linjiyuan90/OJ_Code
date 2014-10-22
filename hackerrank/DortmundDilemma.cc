/*
  How many strings of len N which are formed exactly from K distinct characters and 
  each string has a **proper** prefix = suffix. Proper means prefix != str.
  N <= 10^5, K <= 26
  
  https://hr-filepicker.s3.amazonaws.com/101jun14/3124-Dortmund-Dilemma.pdf

  Consider the reverse problem, how many strings has **no proper** prefix & suffix.
  Let F(N, K) be the ways of strings has **no proper** preffix & suffix, and the characters
  comes from 1...K, and may not use all K char, then
  F(N, K) = K, N = 1
            F(N-1, K)*K, N is odd. insert the new one in the middle
            F(N-1, K)*K - F(N/2, K), N is even. 
  
  let G(N, K) for strings has **at least one proper** prefix & suffix
  (but may no have all the K characters)
  G(N, K) = K^N - F(N, K)
  
  let P(N, K) for strings has exactly K characters, then
  P(N, K) = G(N, K),  K = 1
            G(N, K) - ∑P(N, j) * C(K, j), j = 1..K-1

  The answer will be P(N, K) * C(26, K)

  An interesting problem!
  Consider reverse counting problem, rethink about F[][], P[][]
*/

#include "iostream"
#include "vector"
#include "algorithm"
#include "numeric"

const int Mod = 1000000009;
const int MaxN = 100000;
const int MaxK = 26;

int F[MaxN + 1][27];
int G[MaxN + 1][27];
int P[MaxN + 1][27];
int C[MaxK + 1][MaxK + 1];

void init() {
  for (int i = 0; i <= MaxK; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = (C[i-1][j] + C[i-1][j-1]) % Mod;
    }
  }
  std::iota(F[1], F[1] + MaxK + 1, 0);
  for (int K = 1; K <= MaxK; ++K) {
    int kn = K;
    for (int N = 2; N <= MaxN; ++N) {
      kn = 1ll * kn * K % Mod;
      if (N % 2 == 0) {
        F[N][K] = (1ll * F[N-1][K] * K % Mod - F[N/2][K] + Mod) % Mod;
      } else {
        F[N][K] = 1ll * F[N-1][K] * K % Mod;
      }
      G[N][K] = (kn - F[N][K] + Mod) % Mod;
      P[N][K] = G[N][K];
      for (int j = 1; j < K; ++j) {
        P[N][K] = (P[N][K] - 1ll * P[N][j] * C[K][j] % Mod + Mod) % Mod;
      }
    }
  }
}

int main() {
  init();
  int T, N, K;
  for (std::cin >> T; T--; ) {
    std::cin >> N >> K;
    std::cout << 1ll * P[N][K] * C[26][K] % Mod << std::endl;
  }
  return 0;
}
