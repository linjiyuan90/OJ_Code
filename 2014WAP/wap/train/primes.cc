#include "iostream"
#include "map"
#include "vector"

const int MAX_N = 10000;

std::vector<int> init_prime(int n) {	
  std::vector<int> primes;
  std::vector<bool> is_prime(n + 1, true);
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      // note if i * i will overflow
      for (int j = i * i; j <= n; j += i) {
	is_prime[j] = false;
      }
    }
  }
  return primes;
}

void dfs(int p,
	 int q,
	 int i,
	 std::vector<int> &primes,
	 std::map<int, std::vector<int>> &ans) {
  if (i >= primes.size()) {
    ans[q].push_back(p);
    return;
  }
  if (p % primes[i] != 0 && q * primes[i] < p) {
    dfs(p, q * primes[i], i, primes, ans);
  }
  dfs(p, q, i + 1, primes, ans);
}

int main() {
  auto primes = init_prime(MAX_N);
  for (int n, m; std::cin >> n >> m; ) {
    std::map<int, std::vector<int>> ans;
    for (int p = n; p <= m; ++p) {
      dfs(p, 1, 0, primes, ans);
    }
    for (auto &e : ans) {
      int q = e.first;
      for (auto &p : e.second) {
	std::cout << q << "/" << p << " ";
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
