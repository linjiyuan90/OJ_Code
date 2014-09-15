#include "iostream"
#include "string"
#include "vector"
#include "list"
#include "map"
#include "cassert"

using namespace std;

namespace Parentheses {
const int Max = 10;
std::vector<unsigned long long> f(Max + 1);

void init() {
  f[0] = 1;
  for (int n = 1; n <= Max; ++n) {
    for (int i = 0; i < n; ++i) {
      f[n] += f[i] * f[n-1-i];
      double ff = f[i];
      ff *= f[n-1-i];
      assert(f[i] * f[n-1-i] >= ff);
    }
  }
}

// k start from zero
std::string construct(int n, unsigned long long k) {
  // std::cout << n << " " << f[n] << " " << k << std::endl;
  assert(f[n] > k);
  if (k == 0) {
    return std::string(n, '(') + std::string(n, ')');
  }
  unsigned long long sum = 0;
  // enumerate the first ()
  int i;
  for (i = n; i > 0; --i) {
    if (sum + f[n-i+1] > k) {
      break;
    }
    sum += f[n-i+1];
  }
  // enumerate how much inside
  // (inside) outside
  int in;
  // unsigned long long sum = 0;
  for (in = n-i; in >= 0; --in) {
    if (sum + f[n-i-in] > k) {
      break;
    }
    sum += f[n-i-in];
  }
  k -= sum;
  unsigned long long m = k / f[n-i-in];
  std::string res = std::string(i, '(') + ")";
  res += construct(in, m) + std::string(i-1, ')');
  res += construct(n-i-in, k % f[n-i-in]);
  return res;
}

std::vector<std::string> construct(int n) {
  if (n == 0) {
    return {""};
  }
  if (n == 1) {
    return {"()"};
  }
  std::vector<std::string> res;
  for (int left = 0; left < n; ++left) {
    for (const auto& l : construct(left)) {
      for (const auto& r : construct(n - 1 - left)) {
        res.push_back("(" + l + ")" + r);
      }
    }
  }
  return res;
}

std::string constructByBruteForce(int n, unsigned long long k) {
  auto res = construct(n);
  std::sort(res.begin(), res.end());
  return res[k];
}

}


int main() {
  Parentheses::init();
  int T, n, t = 1;
  long long k;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n >> k;
    if (k > Parentheses::f[n]) {
      std::cout << "Doesn't Exist!" << std::endl;
    } else {
      std::cout << Parentheses::constructByBruteForce(n, k-1) << std::endl;
      // std::cout << Parentheses::construct(n, k-1) << std::endl;
    }
  }
  return 0;
}
