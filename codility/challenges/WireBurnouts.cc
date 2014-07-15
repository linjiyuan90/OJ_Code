#include "vector"
#include "numeric"
#include "algorithm"

const std::vector<std::pair<int, int>> Directions = {
  {0, 1},
  {1, 0}
};

template<typename A, typename B>
class PairHash {
  std::hash<A> hashA;
  std::hash<B> hashB;
public:
  std::size_t operator()(const std::pair<A, B>& pair) const {
    return hashA(pair.first) ^ hashB(pair.second);
  }
};

class DisjointSet {
  std::vector<int> link, rank; 
public:
  DisjointSet(int n): link(n), rank(n, 1) {
    std::iota(link.begin(), link.end(), 0);
  }
  
  int find(int a) {
    return a != link[a] ? link[a] = find(link[a]) : a;
  }
  
  bool merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (rank[a] > rank[b]) {
      std::swap(a, b);
    }
    if (a != b) {
      link[a] = b;
      rank[b] = std::max(rank[b], rank[a] + 1);
      return true;
    }
    return false;
  }
  
  bool isLinked(int a, int b) {
    return find(a) == find(b);
  }
};

int solution(int N, const std::vector<int> &A, const std::vector<int> &B, const std::vector<int> &C) {
  auto getId = [&N](int x, int y) {
    return x * N + y;
  };
  int n = N*N, m = A.size();
  std::vector<int> fires(n);
  for (int i = 0; i < m; ++i) {
    fires[getId(A[i], B[i])] |= 1 << C[i];
  }
  DisjointSet ds(n);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int a = getId(i, j);
      for (std::size_t c = 0; c < Directions.size(); ++c) {
	if (fires[a] & (1<<c)) {
	  continue;
	}
	auto d = Directions[c];
	int ii = i + d.first, jj = j + d.second;
	if (0 <= ii && ii < N && 0 <= jj && jj < N) {
	  int b = getId(ii, jj);
	  ds.merge(a, b);
	}
      }
    }
  }
  int s = getId(0, 0), t = getId(N-1, N-1);
  if (ds.isLinked(s, t)) {
    return -1;
  }
  for (int i = m - 1; i >= 0; --i) {
    int a = getId(A[i], B[i]);
    int b = getId(A[i]+Directions[C[i]].first, B[i]+Directions[C[i]].second);
    ds.merge(a, b);
    if (ds.isLinked(s, t)) {
      return i+1;
    }
  }
  return -1;
}
