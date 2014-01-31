#include "algorithm"
#include "numeric"
#include "deque"
#include "vector"
#include "functional"
#include "iostream"

class Solution {
public:
  
  // The most elegant solution
  // https://github.com/Dionysus1227/edocteel/blob/master/Gas%20Station.cc
  // gready
  // The intrinsic meansing is "leave the most expensive traval to the last"
  int canCompleteCircuit(std::vector<int> &gs, std::vector<int> &cost) {
    int delta = 0;
    int min_index = -1, min_sum = INT_MAX;
    for (size_t ix = 0; ix < gs.size(); ++ix) {
      delta += gs[ix] - cost[ix];
      if (delta < min_sum) {
	min_sum = delta;
	min_index = ix;
      }
    }
    return delta < 0 ? -1 : (min_index + 1) % gs.size();
  }
  

  // Enlightened by the above solution
  // Find the max continous sum (may cross the tail to the head) 
  // The intrinsic meaning is "gather as much gas as possible at the begining" 
  int canCompleteCircuit(std::vector<int> &gs, std::vector<int> &cost) {
    int delta = 0;
    std::vector<int> dp(gs.size()),dp_ix(gs.size());
    int max_index = -1, max_sum = -1;
    for (size_t ix = 0; ix < gs.size(); ++ ix) {
      int d = gs[ix] - cost[ix];
      delta += d;
      if (ix == 0 || dp[ix-1] <= 0) {
	dp[ix] = d;
	dp_ix[ix] = ix;
      } else {
	dp[ix] = dp[ix-1] + d;
	dp_ix[ix] = dp_ix[ix-1];
      }
      if (dp[ix] > max_sum) {
	max_sum = dp[ix];
	max_index = dp_ix[ix];
      }
    }
    // cross the tail and head
    if (max_index == 0 && dp.back() > 0) {
      max_index = dp_ix.back();
    }
    return delta < 0 ? -1 : max_index;
  }
  
  // maintain montonically increasing queue
  int canCompleteCircuit2(std::vector<int> &gs, std::vector<int> &cost) {
    // just to make sure
    // sum(gs[s..j]) - sum(cost[s..j]) >= 0 for each j > s if we specify s as start station
    // this is equivalent to
    // min(sum(gs[s..j]) - sum(cost[s..j])) >= 0
    // or,
    // min(sum(gs[1..j] - cost[1..j])) >= sum(gs[1..s-1] - cost[1..s-1])
    // so, we can enumerate s,
    // then check the minimum of sum(gs[1..j] - cost[1..j])
    // the O(n) algorithm can be done by maintaining a monotonically increasing queue

    int n  = gs.size();
   
    // std::partial_sum, std::copy, std::transform seems not so elegant 
    // as manually for --!
    auto diff_sum = std::vector<int>(2*n, 0);
    for (size_t ix = 0; ix < n; ++ix) {
      diff_sum[ix] = (ix == 0 ? 0 : diff_sum[ix - 1]) + (gs[ix] - cost[ix]);
    }
    for (size_t ix = n; ix < 2*n; ++ix) {
      diff_sum[ix] = diff_sum[ix -1] + (gs[ix - n] - cost[ix - n]);
    }
    // maintain a monotonous increasing queue
    std::deque<int> dq;
    for (int i = 0; i < 2*n; ++i) {
      while (!dq.empty() && dq.front() <= i - n) {
	dq.pop_front();
      }
      while (!dq.empty() && diff_sum[dq.back()] >= diff_sum[i]) {
	dq.pop_back();
      }
      dq.push_back(i);
      if (i >= n) {
	// now check the minimal between (i-n, i]
	if (diff_sum[dq.front()] >= diff_sum[i-n]) {
	  return (i-n+1) % n;
	}
      }
    }
    return -1;
  }
};

int main() {
  Solution sol;
  std::vector<int> gs{4}, cost{5};
  std::cout << sol.canCompleteCircuit(gs, cost) << std::endl;
  return 0;
}
