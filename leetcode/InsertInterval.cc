#include "iostream"
#include "vector"
#include "algorithm"

struct Interval {
  int start;
  int end;
  Interval(): start(0), end(0) {}
  Interval(int s, int e): start(s), end(e) {}
};

class Solution {
public:
  std::vector<Interval> insert(std::vector<Interval> &intervals, Interval newInterval) {
    bool is_inserted = false;
    for (auto it = intervals.begin(), pit = intervals.end(); ; ++it) {
      if (it == intervals.end() || newInterval.end < it->start) {
	if (pit != intervals.end()) {
	  it = intervals.erase(pit, it); // note, it will be changed here!
	}
	intervals.insert(it, newInterval);
	break;
      } else if (newInterval.start <= it->end) {
	newInterval.start = std::min(it->start, newInterval.start);
	newInterval.end = std::max(it->end, newInterval.end);
	if (pit == intervals.end()) {
	  // instead of erasing it each time, store the first it
	  pit = it;
	}
      }
    }
    return intervals;
  }
};

int main() {
  Solution sol;
  auto intervals = std::vector<Interval>{Interval(2, 4), Interval(5, 7), Interval(8, 10), Interval(11, 13)};
  auto res = sol.insert(intervals, Interval(3, 8));
  return 0;
}
