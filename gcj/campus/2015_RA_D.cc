/*
  Calculate minimum number of size M*M papers that can cut 2^s1, 2^s2, ..., 2^sk squares.
  Since its length is power of 2, it's easy to maintain these squares in M.
  Once one square 2^sk is cut in M, collect the left pieces.
  Cut larger sqaures first.
*/

#include "iostream"
#include "vector"

class Matrix {
  int M;
  std::vector<int> tiles;
  
  // Find max k that: 2^k <= m
  int getK(int m) {
    int k = 0;
    while (m > 1) {
      m >>= 1;
      ++k;
    }
    return k;
  }

  void incTiles(int a, int b, std::vector<int>& tiles) {
    if (a > b) {
      std::swap(a, b);
    }
    if (a == 0) {
      return;
    }
    if (a == 1) {
      tiles[0] += b;
      return;
    }
    int ak = getK(a), sa = 1 << ak;
    int ac = a / sa, bc = b / sa;
    tiles[ak] += ac * bc;
    incTiles(b - sa * bc, a, tiles);
    incTiles(a - sa * ac, sa * bc, tiles);
  }
  
public:
  Matrix(int _M) {
    M = _M;
    tiles.resize(32);
    incTiles(M, M, tiles);
  }
  void print() {
    for (int i = 0; i < 32; ++i) {
      if (tiles[i] > 0) {
        std::cout << i << " " << (1<<i) << " " << tiles[i] << std::endl;
      }
    }
  }
  bool add(int s) {
    for (int i = s; i < 31; ++i) {
      if (tiles[i] > 0) {
        -- tiles[i];
        incTiles((1<<i)-(1<<s), 1<<i, tiles);
        incTiles(1<<s, (1<<i)-(1<<s), tiles);
        return true;
      }
    }
    return false;
  }
};

int main() {
  int T, t = 1, m, n;
  for (std::cin >> T; T--; ++t) {
    std::cout << "Case #" << t << ": ";
    std::cin >> n >> m;
    std::vector<int> sn(n);
    for (auto& s : sn) {
      std::cin >> s;
    }
    std::vector<Matrix> ans;
    std::sort(sn.begin(), sn.end());
    for (auto it = sn.rbegin(); it != sn.rend(); ++it) {
      bool added = false;
      for (auto& m : ans) {
        if (m.add(*it)) {
          added = true;
          break;
        }
      }
      if (!added) {
        ans.push_back(Matrix(m));
        ans.back().add(*it);
      }
    }
    /*
      Matrix(m).print();
      for (auto& m : ans) {
      m.print();
      }*/
    std::cout << ans.size() << std::endl;
  }
  return 0;
}
