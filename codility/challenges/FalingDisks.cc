#include "deque"

typedef std::pair<int, int> IntPair;

int solution(vector<int> &A, vector<int> &B) {
  // maintain an narrowing well
  int n = A.size();
  std::deque<IntPair> well;  // {wide, height}
  for (int i = n-1; i >= 0; --i) {
    while(!well.empty() && well.back().first >= A[i]) {
      well.pop_back();
    }
    well.push_back({A[i], n - 1 - i});
  }
  int now = 0, m = 0;
  for (auto& b : B) {
    int base = 0;
    while(!well.empty() && well.front().first < b) {
      base = well.front().second + 1;
      well.pop_front();
    }
    // well is too narrow
    if (well.empty()) {
      return m;
    }
    now = std::max(now, base);
    if (now++ < n) {
      ++ m;
    }
  }
  return m;
}
