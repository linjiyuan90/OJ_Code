
// Note the bianry search
// when m1 == m2, need to --m1, ++m2
// For example
// 0 0 2
// 2 2 0

#include "vector"
#include "algorithm"
#include "iostream"
#include "cmath"

struct Area {
  int x1, y1, x2, y2;
};

long long sum_dist(const std::vector<Area> &areas,
		   long long v, bool x_or_y) {
  long long sum = 0;
  for (auto &area : areas) {
    long long v1 = area.x1, v2 = area.x2, n = (area.y2 - area.y1 + 1);
    if (!x_or_y) {
      v1 = area.y1;
      v2 = area.y2;
      n = (area.x2 - area.x1 + 1);
    }
    long long d = 0;
    if (v1 > v || v2 < v) {
      d = ::llabs(v2-v + v1-v) * (v2-v1+1)/2;
    } else {
      d = (v-v1)*(v-v1+1)/2 + (v2-v)*(v2-v+1)/2;
    }
    sum += n*d;
  }
  return sum;
}

int binary_search(const std::vector<Area> &areas,
		  int lo, int hi, bool x_or_y) {
  while(lo < hi) {
    int len = (hi - lo + 1)/3;
    int m1 = lo + len, m2 = hi - len;
    if (m1 == m2) { // note
      -- m1;
      ++ m2;
    }
    long long sm1 = sum_dist(areas, m1, x_or_y);
    long long sm2 = sum_dist(areas, m2, x_or_y);
    if (sm1 <= sm2) {
      hi = m2 - 1;
    } else {
      lo = m1 + 1;
    }
  }
  return lo;
}

int brute_force_search(const std::vector<Area> &areas,
		       int lo, int hi, bool x_or_y) {
  long long sum = LONG_MAX;
  int mv;
  for (int v = lo; v <= hi; ++v) {
    long long s = sum_dist(areas, v, x_or_y);
    if (s < sum) {
      sum = s;
      mv = v;
    }
  }
  return mv;
}

std::vector<long long> find_optimal(const std::vector<Area> &areas) {
  long long min = LONG_MAX;
  int x, y;
  for (auto &area: areas) {
    // int xx = brute_force_search(areas, area.x1, area.x2, true);
    // int yy = brute_force_search(areas, area.y1, area.y2, false);
    int xx = binary_search(areas, area.x1, area.x2, true);
    int yy = binary_search(areas, area.y1, area.y2, false);
    long long sum = sum_dist(areas, xx, true) + sum_dist(areas, yy, false);
    if (sum < min || sum == min && (x > xx || x == xx && y > yy)) {
      min = sum;
      x = xx;
      y = yy;
    }
  }
  return {x, y, min};
}

int main() {
  int T;
  std::cin >> T;
  for (int n, t = 1; t <= T; ++t) {
    std::cin >> n;
    auto areas = std::vector<Area>(n);
    for (auto &area : areas) {
      std::cin >> area.x1 >> area.y1 >> area.x2 >> area.y2;
    }
    std::cout << "Case #" << t << ":";
    for (auto e : find_optimal(areas)) {
      std::cout << " " << e;
    }
    std::cout << std::endl;
  }
  return 0;
}
