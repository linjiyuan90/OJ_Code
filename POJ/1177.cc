/*
  Union of rectangle perimeter
  O(n^2)
  
  Use IntervalTree to make it O(nlogn)
*/

#include "iostream"
#include "vector"
#include "algorithm"
#include "set"

enum State {
  OPEN, CLOSED
};

struct Segment {
  int st, ed;
  State state;
  Segment(int st, int ed, State state) : st(st), ed(ed), state(state) {
  }
  bool operator < (const Segment& that) const {
    return st < that.st || (st == that.st && ed < that.ed)
    || (st == that.st && ed == that.ed && state < that.state);
  }
};

struct Rectangle {
  int xLeft, yLeft, xRight, yRight;
  // swap x and y
  void rotate() {
    std::swap(xLeft, yLeft);
    std::swap(xRight, yRight);
  }
};

int segIntersect(int st1, int ed1, int st2, int ed2) {
  if (st1 > ed2 || st2 > ed1) {
    return 0;
  }
  return std::min(ed1, ed2) - std::max(st1, st2);
}

// calculate perimeter of y axis
int rectangleVerticalPerimeter(std::vector<Rectangle>& rectangles) {
  int perimeter = 0;
  // (x, verticalSegment)
  std::vector<std::pair<int, Segment> > verticalSegments;
  // for (auto& rect : rectangles) {
  for (int i = 0, n = rectangles.size(); i < n; ++i) {
    const Rectangle& rect = rectangles[i];
    verticalSegments.push_back({rect.xLeft, Segment(rect.yLeft, rect.yRight, OPEN)});
    verticalSegments.push_back({rect.xRight, Segment(rect.yLeft, rect.yRight, CLOSED)});
  }
  std::sort(verticalSegments.begin(), verticalSegments.end());
  std::set<Segment> curSegments;
  // for (auto& vSeg : verticalSegments) {
  for (int i = 0, n = verticalSegments.size(); i < n; ++i) {
    std::pair<int, Segment> vSeg = verticalSegments[i];
    if (vSeg.second.state == OPEN) {
      curSegments.insert(vSeg.second);
    } else {
      // find all intervals that has only one count
      std::vector<std::pair<int, State> > points;
      // for (auto& seg : curSegments) {
      for (std::set<Segment>::iterator it = curSegments.begin(); it != curSegments.end(); ++it) {
        const Segment& seg = *it;
        points.push_back({seg.st, OPEN});
        points.push_back({seg.ed, CLOSED});
      }
      std::sort(points.begin(), points.end());
      // only calculate those edge with cnt = 1
      for (int cnt = 0, last, i = 0, n = points.size(); i < n; ++i) {
        if (points[i].second == OPEN) {
          if (++cnt == 2) {
            perimeter += segIntersect(last, points[i].first, vSeg.second.st, vSeg.second.ed);
          }
        } else {
          if (--cnt == 0) {
            perimeter += segIntersect(last, points[i].first, vSeg.second.st, vSeg.second.ed);
          }
        }
        last = points[i].first;
      }
      vSeg.second.state = OPEN;
      curSegments.erase(vSeg.second);
    }
  }
  return perimeter;
}

int rectanglePerimeter(std::vector<Rectangle>& rectangles) {
  int perimeter = rectangleVerticalPerimeter(rectangles);
  // for (auto& rect : rectangles) {
  for (int i = 0, n = rectangles.size(); i < n; ++i) {
      Rectangle& rect = rectangles[i];
      rect.rotate();
  }
  return (perimeter + rectangleVerticalPerimeter(rectangles)) * 2;
}

int main() {
  for (int n; std::cin >> n;) {
    std::vector<Rectangle> rectangles(n);
    // for (auto& rect : rectangles) {
    for (int i = 0; i < n; ++i) {
      Rectangle& rect = rectangles[i];
      std::cin >> rect.xLeft >> rect.yLeft >> rect.xRight >> rect.yRight;
    }
    std::cout << rectanglePerimeter(rectangles) << std::endl;
  }
  return 0;
}
