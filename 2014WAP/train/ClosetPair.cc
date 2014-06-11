/*
  Closet pair problem with divide and conquer algorithm O(nlogn)
  uva 10245
  the merge operation is:
  find a strip with points where abs(x - midx) < d, d = min(left, right)
  then for each point in the strip, check its neighbor
  By neighbor, I mean abs(y - that.y) < d
  It can be proved that at most 6 points in its neighbor!
      |---|---|
  2d/3|   |   |
      |---|---|
  2d/3|   |   |
      |---|---|
      |   |   |
  2d/3|---|---|
       d/2 d/2
   There will be at most one point in each grid, otherwise
   (2d/3)^2 + (d/2)^2 = (25/36d)^2 < d^2
*/
#include "iomanip"
#include "iostream"
#include "vector"
#include "algorithm"
#include "cmath"

const double DOUBLE_MAX = 1e300;

class Point {
public:
  double x, y;
  bool operator < (const Point &that) const {
    return x < that.x || (x == that.x && y < that.y);
  }
  double dist(const Point &that) const {
    double dx = x - that.x, dy = y - that.y;
    return sqrt(dx * dx + dy * dy);
  }
  friend std::istream& operator >> (std::istream &is, Point &p);
};

std::istream& operator >> (std::istream &is, Point &p) {
  is >> p.x >> p.y;
  return is;
}

typedef std::vector<Point>::const_iterator Iter;

double closet_pair(Iter begin, Iter end) {
  if (end - begin < 2) {
    // throw std::invalid_argument("Num of points is less than 2");
    return DOUBLE_MAX;
  }
  if (end - begin == 2) {
    return begin->dist(*(begin + 1));
  }
  Iter mid = begin + (end - begin) / 2;
  double d = std::min(closet_pair(begin, mid), closet_pair(mid, end));
  std::vector<Point> strip;
  for (Iter it = begin; it < end; ++it) {
    if (abs(it->x - mid->x) < d) {
      strip.push_back(*it);
    }
  }
  std::sort(strip.begin(), strip.end(), [](const Point &a, const Point &b) {
    return a.y < b.y;
  });
  for (int i = 0; i < strip.size(); ++i) {
    for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; ++j) {
      d = std::min(d, strip[i].dist(strip[j]));
    }
  }
  return d;
}

int main() {
  for (int n; std::cin >> n, n; ) {
    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> points[i];
    }
    std::sort(points.begin(), points.end());
    double ans = closet_pair(points.cbegin(), points.cend());
    if (ans > 10000) {
      std::cout << "INFINITY" << std::endl;
    } else {
      std::cout << std::fixed << std::setprecision(4) << ans << std::endl;
    }
  }
  return 0;
}
