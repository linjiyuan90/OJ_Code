class Solution {
public:
  vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
    std::vector<Interval> ans;
    bool inserted = false;
    for (Interval &interval : intervals) {
      // non-overlap
      if (interval.end < newInterval.start) {
	ans.push_back(interval);
      } else if (interval.start > newInterval.end) {
	if (!inserted) {
	  ans.push_back(newInterval);
	  inserted = true;
	}
	ans.push_back(interval);
      } else {
	newInterval.start = std::min(newInterval.start, interval.start);
	newInterval.end = std::max(newInterval.end, interval.end);
      }
    }
    if (!inserted) {
      ans.push_back(newInterval);
    }
    return ans;
  }
};
