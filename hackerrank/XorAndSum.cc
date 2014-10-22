/*
  Given two binary string, calculate ∑(a xor (b shl i)), i = 0...314159
  bj will xor [a_{j+ShiftLen}, aj]
  store all zero sum and all one sum of [a_{j+ShiftLen}, aj], then slide this window...
*/
#include "iostream"
#include "vector"
#include "string"
#include "algorithm"

const int ShiftLen = 314159;
const int Mod = 1000000007;

int xorAndSum(const std::string& a, const std::string& b) {
  int n = a.size(), m = b.size();
  int sum = 0;
  // xor sum of right extra zeros of b with a
  for (int i = 0, c = 1 ; i < ShiftLen; ++i, c = c * 2 % Mod) {
    if (i < n && a[n-i-1] == '1') {
      sum = (sum + (0ll + ShiftLen - i) * c % Mod) % Mod;
    }
  }
  int zero = 0, one = 0;
  int c = 1;
  for (int i = 0; i <= ShiftLen; ++i, c = c * 2 % Mod) {
    if (i < n && a[n-i-1] == '1') {
      one = (one + c) % Mod;
    } else {
      zero = (zero + c) % Mod;
    }
  }
  // xor sum of bi with [a_{i+ShiftLen}, ai]
  for (int i = 0, rc = 1; i < std::max(n, m);
       ++i, c = c * 2 % Mod, rc = rc * 2 % Mod) {
    char bi = i < m ? b[m-i-1] : '0';
    if (bi == '0') {
      sum = (sum + one) % Mod;
    } else {
      sum = (sum + zero) % Mod;
    }
    // add new left bit
    int li = i + ShiftLen + 1;
    if (li < n && a[n-li-1] == '1') {
      one = (one + c) % Mod;
    } else {
      zero = (zero + c) % Mod;
    }
    // remove old right bit
    if (i < n && a[n-i-1] == '1') {
      one = (one - rc + Mod) % Mod;
    } else {
      zero = (zero - rc + Mod) % Mod;
    }
  }
  return sum;
}

int main() {
  for (std::string a, b; std::cin >> a >> b;) {
    std::cout << xorAndSum(a, b) << std::endl;
  }
  return 0;
}


