#include "algorithm"

// O(NM)
int solution(const vector<int> &A) {
  // the approach which try to find a combination closest to sum/2 requires time O(N^2M)
  // Instead, redefine the dp: try to find combination in range [-M, M] using A[0]...A[i]
  // Time O(NM)
  auto minmax = std::minmax(A.begin(), A.end());
  int M = std::max(::abs(*minmax.first), ::abs(*minmax.second));
  std::vector<bool> pre(2*M+1), now(2*M+1);
  // [-M, M]
  pre[M+0] = true;
  for (int i = 0, n = A.size(); i < n; ++i) {
    std::fill(now.begin(), now.end(), false);
    for (int j = -M; j <= M; ++j) {
      if (!pre[M +j]) {
	continue;
      }
      // -A[i]
      if (-M <= j - A[i] && j - A[i] <= M) {
	now[M + j - A[i]] = true;
      }
      // +A[i]
      if (-M <= j + A[i] && j + A[i] <= M) {
	now[M + j + A[i]] = true;
      }
    }
    std::swap(pre, now);
  }
  return std::min(
		  std::find(pre.rbegin() + M, pre.rend(), true) - (pre.rbegin() + M),
		  std::find(pre.begin() + M, pre.end(), true) - (pre.begin() + M)
		  );
}

/*
  https://codility.com/media/train/solution-min-abs-sum.pdf
  
  The offical solution is to count number of each elements, then do a knapback
  where each item has some number. The complexity is O(NM^2)
  when in item[i], let dp[j]
  -1: means unavailable
  >=0: means how many item[i] is left after reach j
  The tranformation is:
  if dp[j] >= 0: dp[j] = count[item[i]]
  elif dp[j-item[i]] > 0: dp[j] = dp[j-item[i]]-1
*/

// O(NM^2)
int solution(const std::vector<int>& A) {
  auto minmax = std::minmax(A.begin(), A.end());
  int M = std::max(::abs(*minmax.first), ::abs(*minmax.second));
  std::vector<int> count(M+1);
  int sum = 0;
  for (auto& a : A) {
    ++count[::abs(a)];
    sum += ::abs(a);
  }
  std::vector<int> dp(sum+1, -1);
  dp[0] = 0;
  for (int a = 1; a <= M; ++a) {
    if (count[a] > 0) {
      for (int j = 0; j <= sum; ++j) {
	if (dp[j] >= 0) {
	  dp[j] = count[a];
	} else if (j >= a && dp[j-a] > 0) {
	  dp[j] = dp[j-a] - 1;
	}
      }
    }
  }
  int res = sum;
  for (int j = sum / 2; j <= sum; ++j) {
    if (dp[j] >= 0) {
      res = std::min(res, ::abs(sum - 2*j));
    }
  }
  return res;
}
