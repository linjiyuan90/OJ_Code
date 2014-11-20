/*
  Find the longest prefix, that's also a suffix and occure somewhere in the
  string that doesn't overlap the prefix and suffix.
  
  1. First getNext() (next is also called borders)
  2. mark next[n-1], next[next[n-1]], ..., they are prefix candidates
  3. try every j, if j has common prefix with n-1, that's: next[next..[j]] = next[next..[n-1]]
  then for each prefix candidates c, check whether c <= next[j] && c < j - c && j < n-1 - c

  Conclusion: next[] forms an tree, several i may have same parent
*/

#include "vector"
#include "algorithm"

std::vector<int> getNext(const std::string& S) {
  int n = S.size();
  std::vector<int> next(n);
  if (n > 0) {
    next[0] = -1;
    for (int i = 1; i < n; ++i) {
      for (next[i] = next[i-1] + 1; next[i] >= 0 && S[next[i]] != S[i]; ) {
	next[i] = next[i] == 0 ? -1 : next[next[i]-1] + 1;
      }
    }
  }
  return next;
}

int solution(string& S) {
  int n = S.size();
  auto next = getNext(S);
  std::vector<int> candidates;  // available prefixs which are also suffix
  std::vector<bool> mark(n);
  for (int i = n - 1; i >= 0; i = next[i]) {
    mark[i] = true;
    candidates.push_back(i);
  }
  int l = 0;
  for (int j = 0; j < n; ++j) {
    // mark means j and n-1 has common prefix candidates
    // Or say, some S[next...[j]] = S[next..[n-1]]
    if (next[j] >= 0 && mark[next[j]]) {
      while (!candidates.empty()) {
	int c = candidates.back();
	// note c <= next[j]
	if (c <= next[j] && c < j - c && j < n-1 - c) {  // is this judge perfect?
	  l = std::max(l, c + 1);
	  candidates.pop_back();
	} else {
	  break;
	}
      }
      mark[j] = true;
    }
  }
  return l;
}

// 'abaa'
// 'abababbbabbbaba'
