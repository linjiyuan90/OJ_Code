#include "iostream"
#include "vector"
#include "algorithm"
#include "deque"

struct Interval {
  int start;
  int end;
  Interval(): start(0), end(0) {}
  Interval(int s, int e): start(s), end(e) {}
};

class Solution {
public:
  // The intervals are not sorted!
  std::vector<Interval> merge(std::vector<Interval> &intervals) {
    // sort by start will make the merge easier than by end
    std::sort(intervals.begin(),
	      intervals.end(),
	      [](const Interval &a, const Interval &b) {
		return a.start < b.start;
	      });
    std::vector<Interval> ans;
    for (auto e : intervals) {
      if (ans.empty() || ans.back().end < e.start) {
	ans.push_back(e);
      } else {
	ans.back().end = std::max(ans.back().end, e.end);
      }
    }
    return ans;
  }
};

int main() {
  Solution sol;
  auto intervals = std::vector<Interval>{
    Interval(1, 3), Interval(2, 6),
    Interval(15, 18), Interval(8, 10)
  };
  for (auto e : sol.merge(intervals)) {
    std::cout << e.start << " " << e.end << std::endl;
  }
  return 0;
}
