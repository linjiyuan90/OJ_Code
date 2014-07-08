/*
  The native algorithm is to simulate with bucket.
  
  A more smart algorithm is, noted that the dominator is both left & right must
  the dominator globally!
  http://rafal.io/posts/codility-equi-leader.html
*/

#include "unordered_map"
#include "vector"
#include "algorithm"

int solution(std::vector<int>& A) {
  if (A.empty()) {
    return 0;
  }
  int dominator = A[0];
  int cnt = 0;
  for (auto& x : A) {
    if (x == dominator) {
      ++ cnt;
    } else if (--cnt == 0) {
      dominator = x;
      cnt = 1;
    }
  }
  cnt = std::count(A.begin(), A.end(), dominator);
  int res = 0;
  for (int i = 0, n = A.size(), pre_cnt = 0; i < n - 1; ++i) {
    if (A[i] == dominator) {
      ++ pre_cnt;
    }
    if (pre_cnt > (i+1)/2 && (cnt - pre_cnt) > (n-1-i)/2) {
      ++ res;
    }
  }
  return res;
}

class Bucket {
  std::vector<std::vector<int>> buckets {1};
  std::unordered_map<int, std::pair<int, int>> pos; // (cnt, offset)
  
public:
  void increase(int x) {
    int p;
    if (pos.find(x) == pos.end()) { // new elements
      p = 0;
    } else {
      p = pos[x].first;
      int y = buckets[p].back();
      std::swap(pos[x], pos[y]);
      std::swap(buckets[p][pos[x].second], buckets[p][pos[y].second]);
      buckets[p].pop_back();
    }
    if (p == buckets.size() - 1) {
      buckets.push_back({x});
    } else {
      buckets[p+1].push_back(x);
    }
    pos[x] = {p + 1, buckets[p+1].size() - 1};
  }
  
  void decrease(int x) {
    if (pos.find(x) == pos.end()) {
      return;
    }
    int p = pos[x].first;
    int y = buckets[p].back();
    std::swap(pos[x], pos[y]);
    std::swap(buckets[p][pos[x].second], buckets[p][pos[y].second]);
    buckets[p].pop_back();
    if (p > 1) {
      buckets[p-1].push_back(x);
      pos[x] = {p - 1, buckets[p-1].size() - 1};
    } else {
      pos.erase(x);
    }
  }
  
  int max_cnt() {
    return buckets.size();
  }
  
  int max_x() {
    return buckets.back().back();
  }
};

int solution2(std::vector<int> &A) {
  Bucket left, right;
  for (auto& x : A) {
    right.increase(x);
  }
  int res = 0;
  for (int i = 0, n = A.size(); i < n; ++i) {
    left.increase(A[i]);
    right.decrease(A[i]);
    if (left.max_cnt() > (i+1)/2 && right.max_cnt() > (n-i-1)/2
	&& left.max_x() == right.max_x()) {
      ++ res;
    }
  }
  return res;
}
