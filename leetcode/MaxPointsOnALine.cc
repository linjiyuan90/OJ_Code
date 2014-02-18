class Solution {
public:
  int maxPoints(std::vector<Point> &points) {
    int ans = 0;
    int n = points.size();
    // O(n^2logn)
    for (int i = 0; i < n; ++i) {
      auto &s = points[i];
      int inc = 0;
      // unordered_map<std::pair<int, int>, int> not work. why?
      // no hash function?
      // Another approach, store angle/ratio instead of (dx, dy)
      std::map<std::pair<int, int>, int> cnt;
      for (int j = 0; j < n; ++j) {
	auto &e = points[j];
	if (s.x == e.x && s.y == e.y) {
	  ++ inc;
	  continue;
	}
	int dx = e.x - s.x, dy = e.y - s.y;
	int g = gcd(dx, dy);
	dx /= g;
	dy /= g;
	if (dx < 0) {
	  dx = -dx;
	  dy = -dy;
	}
	++ cnt[std::make_pair(dx, dy)];
      }
      ans = std::max(ans, inc);
      for (auto &c : cnt) {
	ans = std::max(ans, c.second + inc);
      }
    }
    return ans;
  }
  
private:
  int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
  }
};

// note points on same position
// (1, 1), (1, 1), (2, 2), (2, 2) return 4
