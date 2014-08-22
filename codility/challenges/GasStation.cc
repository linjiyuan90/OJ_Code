#include "functional"
#include "iterator"
#include "numeric"
#include "algorithm"
#include "vector"
#include "iostream"
#include "stack"

using namespace std;

// at i, add enough oil to reach j that P[j] < P[i]
int solution(vector<int> &D, vector<int> &P, int T) {
  if (std::any_of(D.begin(), D.end(), std::bind2nd(std::greater<int>(), T))) {
    return -1;
  }
  std::vector<long long> sumDist{0};
  // use partial_sum directly will have int overflow problem
  std::copy(D.begin(), D.end(), std::back_inserter(sumDist));
  std::partial_sum(sumDist.begin(), sumDist.end(), sumDist.begin());

  // for each prices[i], find the first right one prices[j] < prices[i]
  std::vector<int> next(P.size());
  /*
    std::stack<int> stk;
    for (int n = P.size(), i = n - 1; i >= 0; --i) {
    while(!stk.empty() && P[stk.top()] >= P[i]) {
    stk.pop();
    }
    next[i] = stk.empty() ? n : stk.top();
    stk.push(i);
    }
  */
  // another way to find next without using a stack
  for (int n = P.size(), i = n - 1; i >= 0; --i) {
    for (next[i] = i + 1; next[i] < n && P[next[i]] >= P[i]; ) next[i] = next[next[i]];
  }
  long long prices = 0;
  for (std::size_t i = 0, n = P.size(), t = 0; i < n; ++i) {
    std::size_t j = next[i];
    if (t < sumDist[j] - sumDist[i]) {
      int add = std::min((long long)T, sumDist[j] - sumDist[i]) - t;
      prices += 1ll * add * P[i];
      if (prices > 1000000000) {
        return -2;
      }
      t += add;
    }
    t -= (sumDist[i+1] - sumDist[i]);
  }
  return prices;
}
