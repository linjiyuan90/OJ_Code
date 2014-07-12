/*
  Given a string, find prefix which has max{len * occurrence}
  First, calculate next array.
  Note that occurrence of S[0..i] is also an occurrence of S[0..next[i]]
  So we can accumulate the count, that's count[next[i]] += count[i]
*/

#include "vector"

// next[i] means:
// S[0..next[i]] == S[..i]
std::vector<int> getNext(std::string& S) {
  int n = S.size();
  std::vector<int> next(n);
  next[0] = -1;
  for (int i = 1; i < n; ++i) {
    for (next[i] = next[i-1] + 1; next[i] >= 0 && S[next[i]] != S[i];) {
      next[i] = next[i] == 0 ? -1 : next[next[i]-1] + 1;
    }
  }
  return next;
}

int solution(string& S) {
  int n = S.size();
  std::vector<int> next = getNext(S);
  std::vector<int> cnt(n);
  for (int i = n - 1; i >= 0; --i) {
    ++ cnt[i];
    if (next[i] != -1) {
      cnt[next[i]] += cnt[i];  // S[0..i] is also an occurence of S[0..next[i]]
    }
  }
  int max = n;
  for (int l = 1; l < n; ++l) {
    if (1000000000 / l < cnt[l-1]) {
      max = 1000000000;
    } else {
      max = std::max(max, l * cnt[l-1]);
    }
  }
  return max;
}
