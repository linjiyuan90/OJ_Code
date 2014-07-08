/*
  Given n segments, calculate the number of intersected pairs, requires O(nlogn) time complexity
  My first solution is to maintain two discs vectors, one is sorted by start, one is sorted by second.
  Then for each disc, binary search to find the number of discs with second < disc.first & first > disc.second

  ★★★
  More beautiful approach is to treat first, second as two events(open, close)!!!
  For each point, if it's first of some segment, ans += current open events!!!
  if it's second of some segment, -- current open events
*/

#include "algorithm"

int solution(const std::vector<int>& A) {
  int n = A.size();
  std::vector<std::pair<long long, bool>> events;
  for (int i = 0; i < n; ++i) {
    events.push_back({0ll + i - A[i], false});  // open first
    events.push_back({0ll + i + A[i], true});
  }
  std::sort(events.begin(), events.end());
  int res = 0;
  int num_open_events = 0;
  for (auto& event : events) {
    if (!event.second) {
      res += num_open_events;
      if (res > 10000000) {
	return -1;
      }
      ++ num_open_events;
    } else {
      -- num_open_events;
    }
  }
  return res;
}

typedef std::pair<long long, long long> Disc;

int solution2(const vector<int> &A) {
  int n = A.size();
  std::vector<Disc> first_discs(A.size()), second_discs(A.size());
  for (int i = 0; i < n; ++i) {
    long long s = 0ll + i - A[i];
    long long e = 0ll + i + A[i];
    first_discs[i] = {s, e};
    second_discs[i] = {s, e};
  }
  auto first_cmp = [](const Disc& a, const Disc& b) {
    return a.first < b.first;
  };
  auto second_cmp = [](const Disc& a, const Disc& b) {
    return a.second < b.second;
  };
  std::sort(first_discs.begin(), first_discs.end(), first_cmp);
  std::sort(second_discs.begin(), second_discs.end(), second_cmp);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    long long x = 0ll + i - A[i];
    auto it = std::lower_bound(second_discs.begin(),
			       second_discs.end(), 
			       Disc(x, x),
			       second_cmp);
    int num_lt = it - second_discs.begin();
    x = 0ll + i + A[i];
    it = std::upper_bound(first_discs.begin(), 
			  first_discs.end(), 
			  Disc(x, x),
			  first_cmp);
    int num_gt = first_discs.end() - it;
    ans += (n - num_lt - num_gt - 1);
    if (ans > 20000000) {
      return -1;
    }
  }
  return ans / 2;
}
