/*
  For each rectangle, store its left and right vertical segment.
  Then sort them as sorting tuple (x, !isLeft, isLeft ? -y : y).

  Create a map<int, int> to count leftYs.
  if isLeft, check if there is any segment contains it
    if not, add (x,y) to answer.
    ++leftYs[y];
  else check if any segment contains it.
    if not, find the first number of the sorted set which less than it, 
    name as firstY, add it to answer (x, firstY) to answer
    --leftYs[y];   

  Note overlapped points!
 */

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Segment {
  tuple<int, bool, int> tp;
public:
  int x;
  int y;
  bool isLeft;

  Segment(int x, int y, bool isLeft): 
    x(x), y(y), isLeft(isLeft), tp(x, !isLeft, isLeft ? -y : y) {}

  bool operator < (const Segment& that) const {
    return tp < that.tp;
  }
};

class Solution {
  vector<Segment> generateSegments(vector<vector<int>>& buildings) {
    vector<Segment> segments;
    for (auto& b : buildings) {
      segments.push_back(Segment(b[0], b[2], true));
      segments.push_back(Segment(b[1], b[2], false));
    }
    sort(segments.begin(), segments.end());
    return segments;
  }

 public:
  vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    vector<Segment> segments = generateSegments(buildings);
    vector<pair<int, int>> ans;
    map<int, int> leftYs;
    for (Segment& segment : segments) {
      if (segment.isLeft) {
        if (leftYs.empty() || (--leftYs.end())->first < segment.y) {
          ans.push_back(make_pair(segment.x, segment.y));
        }
        ++leftYs[segment.y];
      } else {
        auto top = --leftYs.end();
        if (top->first <= segment.y && top->second == 1) {
          auto it = leftYs.lower_bound(segment.y);
          int y = 0;
          if (it != leftYs.begin()) {
            y = (--it)->first;
          }
          ans.push_back(make_pair(segment.x, y));
        }
        if (--leftYs[segment.y] == 0) {
          leftYs.erase(segment.y);
        }
      }
    }
    return ans;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> buildings = {
    {2, 9, 10},
    {3, 7, 15},
    {5, 12, 12},
    {15, 20, 10},
    {19, 24, 8}
  };
  for (const pair<int, int>& points : sol.getSkyline(buildings)) {
    cout << points.first << " " << points.second << endl;
  }
  return 0;
}
