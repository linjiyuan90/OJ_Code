#include "cmath"

#include "iostream"
#include "iterator"
#include "vector"
#include "algorithm"
#include "numeric"

template<typename T>
std::pair<int, int> find_longest_subarray_less_equal_k(const std::vector<T>& A,
						       const T& k) {
  std::vector<T> prefix_sum = {T()};
  std::partial_sum(A.begin(), A.end(), std::back_inserter(prefix_sum));
  std::vector<T> max_prefix_sum;
  std::partial_sum(prefix_sum.begin(), 
		   prefix_sum.end(), 
		   std::back_inserter(max_prefix_sum),
		   [](const T& a, const T& b) {
		     return std::max(a, b);
		   });
  std::pair<int, int> ans{0, 0};
  for (int i = 1, n = A.size(); i <= n; ++i) {
    // need to find first j with prefix_sum[j] >= prefix_sum[i] - k
    // that's first j with max_prefix_sum[j] >= prefix_sum[i] - k
    int j = std::lower_bound(max_prefix_sum.begin(), 
			     max_prefix_sum.begin() + i,
			     prefix_sum[i] - k) - max_prefix_sum.begin();
    if (i - j > ans.second - ans.first) {
      ans = {j, i};
    }
  }
  return ans;
}

template<typename T>
std::pair<int, int> bf(const std::vector<T>& A, const T& k) {
  std::pair<int, int> ans{0, 0};
  for (int i = 0, n = A.size(); i < n; ++i) {
    for (int j = i, sum = 0; j <= n; ++j) {
      if (sum <= k && j - i > ans.second - ans.first) {
	ans = {i, j};
      }
      if (j < n) {
	sum += A[j];
      }
    }
  }
  return ans;
}

int main() {
  for (; true;) {
    int n = ::rand() % 20;
    std::vector<int> vt(n);
    for (auto& e : vt) {
      e = ::rand() % 20 - 10;
    }
    int k = ::rand() % 20 - 10;
    auto a = find_longest_subarray_less_equal_k(vt, k);
    auto b = bf(vt, k);
    if (a != b) {
      std::cout << a.first << " " << a.second 
		<< " " << b.first << " " << b.second << std::endl;
      std::cout << k << std::endl;
      for (auto& e : vt) {
	std::cout << e << " ";
      }
      std::cout << std::endl;
      break;
    }
  }
  return 0;
}
