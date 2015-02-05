
// note std::hash is a type, not function
// when p == o, they can be in any line

class Solution {
    
  typedef std::pair<int, int> int_pair;
 
  template<typename A, typename B>
  class PairHash {
    std::hash<A> a_hash;
    std::hash<B> b_hash;
  public:
    std::size_t operator()(const std::pair<A, B>& p) const {
      return a_hash(p.first) ^ b_hash(p.second);
    }
  };
    
  int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
  }
    
public:
  int maxPoints(std::vector<Point> &points) {
    // enumerate o, then calculate gcd(x - ox, y - oy)
    int res = 0;
    for (auto& o : points) {
      std::unordered_map<int_pair, int, PairHash<int, int>> cnt;
      int num_same = 0;
      for (auto& p : points) {
	if (o.x == p.x && o.y == p.y) {
	  ++ num_same;
	  continue;
	}
	int xx = p.x - o.x, yy = p.y - o.y;
	int g = gcd(xx, yy);
	if (g != 0) {
	  ++ cnt[{xx/g, yy/g}];
	} else {
	  ++ cnt[{xx == 0 ? 0 : 1, yy == 0 ? 0 : 1}];
	}
      }
      res = std::max(res, num_same);
      for (auto& e : cnt) {
	res = std::max(res, e.second + num_same);
      }
    }
    return res;
  }
};
