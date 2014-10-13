/*
  Find the longest subsequence b[] that every group of 4 elements satisfy: 
  b1 = b3, b2 = b4
  
  Greedy!
  Maintain a buffer, when encountering an element v,
  if buffer contains v, then b1, b3 can be set to v, and expect b4 in the
  future that buffer contains as well.
  So, for each elements in the buffer, mark it as candidate b2.
  Note when b2 is v.
*/
#include "iostream"
#include "map"
#include "vector"

std::vector<int> doubleSequence(const std::vector<int>& seq) {
  std::vector<int> res;
  std::vector<int> buf;
  std::map<int, int> cnt;
  std::map<int, int> link;
  for (auto& v : seq) {
    // greedy
    if (link.count(v)) {
      std::vector<int> ab = {link[v], v, link[v], v};
      res.insert(res.end(), ab.begin(), ab.end());
      cnt.clear();
      link.clear();
      buf.clear();
    } else {
      if (cnt.count(v)) {
        // note situation: b2 = v
        int numV = cnt[v];
        while (true) {
          if (buf.back() == v && --numV == 0) {
            break;
          }
          link[buf.back()] = v;
          buf.pop_back();
        }
        cnt[v] = 1;
      }
      ++cnt[v];
      buf.push_back(v);
    }
  }
  return res;
}

int main() {
  for (int n; std::cin >> n; ) {
    std::vector<int> seq(n);
    for (auto& v : seq) {
      std::cin >> v;
    }
    auto res = doubleSequence(seq);
    std::cout << res.size() << std::endl;
    for (int i = 0, m = res.size(); i < m; ++i) {
      std::cout << res[i] << (i == m - 1 ? "\n" : " ");
    }
  }
  return 0;
}
