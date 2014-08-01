/*
  Given n segments, calculate the number of intersected pairs, requires O(nlogn) time complexity
  My first solution is to maintain two discs vectors, one is sorted by start, one is sorted by second.
  Then for each disc, binary search to find the number of discs with second < disc.first & first > disc.second

  ★★★
  More beautiful approach is to treat first, second as two events(open, close)!!!
  For each point, if it's first of some segment, ans += current open events!!!
  if it's second of some segment, -- current open events

  Same as EPI ch13.10 Find Max Concurrent Events
*/

#include "algorithm"

template<typename T>
class Point {
public:
  Point(const T& time, const bool& isEnd): time(time), isEnd(isEnd) {
  }
    
  bool operator < (const Point& that) const {
    return time < that.time || (time == that.time && !isEnd);
  }
    
  T time;
  bool isEnd;
};

int solution(const vector<int> &A) {
  std::vector<Point<long long>> points;
  for (int i = 0, n = A.size(); i < n; ++i) {
    long long a = static_cast<long long>(A[i]);
    points.push_back({i - a, false});
    points.push_back({i + a, true});
  }
  std::sort(points.begin(), points.end());
  int pair_count = 0, count = 0;
  for (auto& p : points) {
    if (p.isEnd) {
      --count;
    } else {
      pair_count += count;
      if (pair_count > 10000000) {
	pair_count = -1;
	break;
      }
      ++count;
    }
  }
  return pair_count;
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
