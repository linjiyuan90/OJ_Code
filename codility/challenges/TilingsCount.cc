/*
  Let f[n-1][mask] be the number of solutions that rows < n have been filled,
  and nth row is filled with mask (1 in bits means filled)
  Construct a transfer matrix M from mask transfers to mask.
  Then f[n] = (f[0] * M^N), and answer is f[n][0].
  Initially, f[0][0] = 1, f[0][others] = 0
*/

#include "iostream"
#include "algorithm"
#include "vector"

const int Mod = 10000007;

typedef std::vector<std::vector<int>> Matrix;

void generateStates(int now, int i, int M, std::vector<int>& states) {
  if (i == M) {
    states.push_back(now);
    return;
  }
  generateStates(now << 1, i+1, M, states);
  if (i + 1 < M) {
    generateStates((now << 2)|3, i + 2, M, states);
  }
}

std::vector<int> generateStates(int M) {
  std::vector<int> states;
  generateStates(0, 0, M, states);
  return states;
}

void generateNextStates(int now, int i, int M, int state, std::vector<int>& nextStates) {
  if (i == M) {
    nextStates.push_back(now);
    return;
  }
  generateNextStates(now << 1, i + 1, M, state , nextStates);
  if (i + 1 < M && (state & (3<<(M-2-i))) == 0) {
    generateNextStates(now << 2, i + 2, M, state , nextStates);
    generateNextStates((now << 2)|3, i + 2, M, state , nextStates);
  }
}

std::vector<int> generateNextStates(int M, int state) {
  std::vector<int> nextStates;
  generateNextStates(0, 0, M, state, nextStates);
  return nextStates;
}

Matrix buildMatrix(int M, const std::vector<int>& states) {
  int n = states.size();
  // nxn
  std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int& nextState : generateNextStates(M, states[i])) {
      matrix[i][std::lower_bound(states.begin(), states.end(), nextState) - states.begin()] = 1;
    }
  }
  return matrix;
}


Matrix matrixMultiplication(const Matrix& A, const Matrix& B) {
  int n = A.size();
  Matrix C(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
	C[i][j] += (1ll * A[i][k] * B[k][j]) % Mod;
	C[i][j] %= Mod;
      }
    }
  }
  return C;
}

Matrix matrixPower(const Matrix& m, int n) {
  if (n == 0) {
    Matrix res = m;
    for (int i = 0, n = m.size(); i < n; ++i) {
      for (int j = 0; j < n; ++j) {
	res[i][j] = i == j;
      }
    }
    return res;
  }
  if (n == 1) {
    return m;
  }
  Matrix res = matrixPower(m, n/2);
  res = matrixMultiplication(res, res);
  if (n &1) {
    return matrixMultiplication(res, m);
  }
  return res;
}

int solution(int N, int M) {
  // f[n-1][110000...11000] -> f[n][...]
  // 1 -> 0, 0 -> 0/1 (if 1, need consecutive 2 1s)
  auto matrix = buildMatrix(M, generateStates(M));
  auto matrix_n = matrixPower(matrix, N);
  // f[0] * M^n
  // the answer is f[n][0]
  return matrix_n[0][0];
}
