class Solution {
public:
  vector<Interval> merge(vector<Interval> &intervals) {
    std::sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
	return a.start < b.start;
      });
    int c = 0;
    for (int i = 0; i < intervals.size(); ++i) {
      if (c == 0 || intervals[c-1].end < intervals[i].start) {
	intervals[c++] = intervals[i];
      } else {  // overlap
	intervals[c-1].end = std::max(intervals[c-1].end, intervals[i].end);
      }
    }
    intervals.resize(c);
    return intervals;
  }
};
