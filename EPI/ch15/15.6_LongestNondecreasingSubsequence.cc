#include "iostream"
#include "vector"

template<typename T>
std::vector<T> longest_nondecreasing_subsequence(const std::vector<T>& A) {
  if (A.empty()) {
    return A;
  }
  int n = A.size();
  std::vector<int> dp(n);
  std::vector<int> pre(n);
  for (int i = 0; i < n; ++i) {
    dp[i] = 1;
    pre[i] = -1;
    for (int j = i - 1; j >= 0; --j) {
      if (A[j] <= A[i] && dp[j] + 1 > dp[i]) {
	dp[i] = dp[j] + 1;
	pre[i] = j;
      }
    }
  }
  int i = n - 1 - (std::max_element(dp.rbegin(), dp.rend()) - dp.rbegin());
  std::vector<T> res(dp[i]);
  for (int l = dp[i] - 1; l >= 0; i = pre[i], --l) {
    res[l] = A[i];
  }
  return res;
}

template<typename T>
std::vector<T> longest_nondecreasing_subsequence_logn(const std::vector<T>& A) {
  if (A.empty()) {
    return A;
  }
  int n = A.size();
  std::vector<T> dp;
  std::vector<int> dp_ix;
  std::vector<int> pre(n);
  for (int i = 0; i < n; ++i) {
    auto it = std::upper_bound(dp.begin(), dp.end(), A[i]);
    if (it == dp.end()) {
      dp.push_back(A[i]);
      pre[i] = dp_ix.empty() ? -1 : dp_ix.back();
      dp_ix.push_back(i);
    } else {
      int k = it - dp.begin();
      dp[k] = A[i];
      pre[i] = k == 0 ? -1 : dp_ix[k-1];  // not pre[dp_ix[k]]
      dp_ix[k] = i;
    }
  }
  std::vector<T> res(dp.size());
  for (int i = dp_ix.back(), l = dp.size() - 1; l >= 0; i = pre[i], --l) {
    res[l] = A[i];
  }
  return res;
}

template<typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& A) {
  bool first = true;
  for (auto& e : A) {
    if (!first) {
      os << " ";
    }
    os << e;
    first = false;
  }
  return os;
}

int main() {
  for (; true; ) {
    int n = rand() % 10;
    std::vector<int> A(n);
    for (auto& e : A) {
      e = rand() % 20;
    }
    auto a = longest_nondecreasing_subsequence(A);
    auto b = longest_nondecreasing_subsequence_logn(A);
    if (a != b) {
      std::cout << a << std::endl;
      std::cout << b << std::endl;
      std::cout << A << std::endl;
      break;
    }
  }
  return 0;
}
