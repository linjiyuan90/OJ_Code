
class Solution {
public:
  // push back the newInterval, sort and merge seems easier
  std::vector<Interval> insert(std::vector<Interval> &intervals, Interval newInterval) {
    intervals.push_back(newInterval);
    std::sort(intervals.begin(), intervals.end(), 
	      [](const Interval &a, const Interval &b) {
		return a.start < b.start;
	      });
    std::vector<Interval> ans;
    for (auto &e : intervals) {
      if (ans.empty() || ans.back().end < e.start) {
	ans.push_back(e);
      } else {
	ans.back().end = std::max(ans.back().end, e.end);
      }
    }
    return ans;
  }
};

// [[1, 5]], [0, 0]
