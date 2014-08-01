/*
  Given a set of events, what's the maximum number of events that take place
  concurrently.
  
  Codility: Number of Disc Intersections
*/

#include "iostream"
#include "vector"
#include "algorithm"

template <typename TimeType>
class Interval {
public:
  TimeType start, finish;
};

template <typename TimeType>
class EndPoint {
public:
  TimeType time;
  bool isStart;
  
  const bool operator < (const EndPoint& that) const {
    return time < that.time || (time == that.time && isStart);
  }
};

template <typename TimeType>
int find_max_concurrent_events(const std::vector<Interval<TimeType>>& A) {
  std::vector<EndPoint<TimeType>> points;
  for (auto& e : A) {
    // this is not a initializer_list, since initializer_list requires same type!
    // So, this is a default constructor?
    points.push_back(EndPoint<TimeType>{e.start, true});
    points.push_back(EndPoint<TimeType>{e.finish, false});
  }
  std::sort(points.begin(), points.end());
  int max_count = 0, count = 0;
  for (auto& e : points) {
    if (e.isStart) {
      max_count = std::max(max_count, ++count);
    } else {
      --count;
    }
  }
  return max_count;
}
