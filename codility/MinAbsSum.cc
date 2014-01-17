#include "iostream"
#include "numeric"
#include "algorithm"
#include "vector"


// ***
// Key observation: ans <= max{abs(Ai)}
// So, maintain prev sum [-100, 100]

int solution(const std::vector<int> &A) {

  const int OFF = 100;

  bool ok[2][202] = {false};
  int prev = 0, now = 1;
  ok[prev][0 + OFF] = true;
  for (std::vector<int>::const_iterator it = A.begin();
       it != A.end(); ++it) {
    // don't forget this
    std::fill(ok[now], ok[now] + 100 + OFF, false);
    int a = *it;
    for (int x = -100; x <= 100; ++x) {
      // put a
      if (-100 <= x + a && x + a <= 100) {
	ok[now][x + a + OFF] |= ok[prev][x + OFF];
      }
      // put -a
      if (-100 <= x - a && x - a <= 100) {
	ok[now][x - a + OFF] |= ok[prev][x + OFF];
      }
    }
    std::swap(prev, now);
  }
  int ans = 100;
  for (int x = 0; x <= 100; ++x) {
    if (ok[prev][x + OFF] || ok[prev][-x + OFF]) {
      ans = std::min(ans, x);
      break;
    }
  }
  return ans;
}

int main() {
  std::cout << solution({10, 5}) << std::endl;
  std::cout << solution({10, 5, 5}) << std::endl;
  std::cout << solution({10, 5, 10}) << std::endl;
  std::cout << solution({10, 5, 10, 10}) << std::endl;
  return 0;
}
