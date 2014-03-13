// swap number with 0 to make array src become array dst

#include "iostream"
#include "vector"
#include "numeric"

void print(const std::vector<int> &vt) {
  for (auto e : vt) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

void rearrange(std::vector<int> &src, std::vector<int> &dst) {
  int n = src.size();
  // pos[x] means value x should go to pos[x]
  /*
  auto pos = std::vector<int>(n);
  for (int ix = 0; ix < n; ++ix) {
    pos[dst[ix]] = ix;
  }
  */
  // Avoid using auxiliary array
  for (int ix = 0; ix < n; ++ix) {
    dst[dst[ix]%n] += ix * n;
  }
  for (int ix = 0; ix < n; ++ix) {
    dst[ix] /= n;
  }
  // now dst[x] means value x should go to dst[x]  
  // check each src[i], whether pos[src[i]] = i
  int zero_ix = std::find(src.begin(), src.end(), 0) - src.begin();
  for (int ix = 0; ix < n; ++ix) {
    // no need to consider zero here, right?
    while (dst[src[ix]] != ix) {
      print(src);
      int s = ix, t = dst[src[ix]];
      if (src[s] == 0 || src[t] == 0) {
	std::swap(src[s], src[t]);
	zero_ix = src[s] == 0? s : t;
      } else {
	// need to use 0 as media
	// now:
	// (s, 0, t)
	std::swap(src[s], src[zero_ix]);
	// (0, s, t)
	std::swap(src[s], src[t]);
	// (t, s, 0)
	std::swap(src[zero_ix], src[t]);
      }
    }
  }
  // restore dst
   for (int ix = 0; ix < n; ++ix) {
    dst[dst[ix]%n] += ix * n;
  }
  for (int ix = 0; ix < n; ++ix) {
    dst[ix] /= n;
  }
}

int main() {
  auto src = std::vector<int>{1, 2, 0, 4, 3};
  auto dst = std::vector<int>{4, 3, 1, 2, 0};
  rearrange(src, dst);
  print(src);
  print(dst);
}
