/*
  Find the union area of rectangle.
  Since n is small, just brute force.
  
  Scan x from left to right, consider every strip.
*/

#include "iostream"
#include "vector"
#include "algorithm"
#include "ostream"
#include "iomanip"
#include "set"

template<typename A, typename B, typename C>
std::pair<A, std::pair<B, C> > make_tuple(const A& a, const B& b, const C& c) {
  return std::make_pair(a, std::make_pair(b, c));
}

class Rectangle {
public:
  double x1, y1, x2, y2;
};

std::istream& operator >> (std::istream& in, Rectangle& rect) {
  return in >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;
}

class Segment {
public:
  Segment(double st, double ed, bool isOpen): st(st), ed(ed), isOpen(isOpen) {
  }
  
  bool operator < (const Segment& that) const {
    return make_tuple(st, ed, isOpen) < make_tuple(that.st, that.ed, that.isOpen);
  }

  double st, ed;
  bool isOpen;
};

double totalArea(const std::vector<Rectangle>& rects) {
  std::vector<std::pair<double, Segment> > segments;
  // for (const auto& rect : rects) {
  for (std::vector<Rectangle>::const_iterator it = rects.begin();
       it != rects.end(); ++it) {
    const Rectangle& rect = *it;
    segments.push_back(std::make_pair(rect.x1, Segment(rect.y1, rect.y2, true)));
    segments.push_back(std::make_pair(rect.x2, Segment(rect.y1, rect.y2, false)));
  }
  std::sort(segments.begin(), segments.end());
  std::set<Segment> curSegments;
  double area = 0;
  double lastX;
  for (std::size_t i = 0, n = segments.size(); i < n; ++i) {
    if (i == 0 || segments[i].first > lastX) {
      double x = segments[i].first - lastX;
      double y = 0;
      double last = -1;
      // for (auto& seg : curSegments) {
      for (std::set<Segment>::iterator it = curSegments.begin();
           it != curSegments.end(); ++it) {
        const Segment& seg = *it;
        if (seg.ed > last) {
          y += seg.ed - std::max(seg.st, last);
        }
        last = std::max(last, seg.ed);
      }
      area += x * y;
      lastX = segments[i].first;
    }
    if (segments[i].second.isOpen) {
      curSegments.insert(segments[i].second);
    } else {
      segments[i].second.isOpen = true;
      curSegments.erase(segments[i].second);
    }
  }
  return area;
}

int main() {
  for (int n, t = 1; std::cin >> n, n; ++t) {
    std::cout << "Test case #" << t << std::endl;
    std::vector<Rectangle> rects(n);
    // for(auto& rect : rects) {
    for (std::vector<Rectangle>::iterator it = rects.begin(); it != rects.end(); ++it) {
      Rectangle& rect = *it;
      std::cin >> rect;
    }
    std::cout << "Total explored area: " 
              << std::fixed << std::setprecision(2)
              << totalArea(rects)
              << std::endl << std::endl;
  }
  return 0;
}
