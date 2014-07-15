#include "algorithm"
#include "numeric"
#include "vector"
#include "functional"

template<typename T>
struct MinFunctor {
  T operator()(const T& a, const T& b) const {
    return std::min(a, b);
  }
};

std::vector<int> solution(const std::vector<int> &A, const std::vector<int> &B) {
  using namespace std::placeholders;
  auto A1 = A;
  int n = A.size();
  int H = *max_element(A.begin(), A.end());
  std::vector<int> first(H + 1, n);
  for (int i = 0; i < n; ++i) {
    first[A[i]] = std::min(first[A[i]], i);
  }
  std::partial_sum(first.rbegin(), first.rend(), first.rbegin(), MinFunctor<int>());
  for (auto b : B) {
    if (b > H || b <= A1[0]) {
      continue;
    }
    int j = first[b];
    if (--j >= 0) {
      ++ A1[j];
      first[A1[j]] = std::min(first[A1[j]], j);
    }
  }
  return A1;
}
