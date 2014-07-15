/*
  Note the distance between first and last hands.
  The core algorithm is to judge whether two cycles are identical.

  There is an algorithm called: **Lexicographically Minimal String Rotation**. 最小表示法？
  For each cycle, find its canonical rotation~
  Then just compare neighbor strings.
  
  Alternative approach is to rotate each string until we get the minimal/maximal hash.
  Then sort by this hash and compare neighbor strings.
*/

template<typename Container>
Container lexicographcally_minimum_seq(const Container& seq) {
  int n = seq.size();
  int i, j, cnt;
  for (i = 0, j = 1, cnt = 0; i < n && j < n && cnt < n;) {
    int ii = (i + cnt) % n;
    int jj = (j + cnt) % n;
    if (seq[ii] == seq[jj]) {
      ++ cnt;
    } else {
      if (seq[ii] > seq[jj]) {
	i = i + cnt + 1;
      } else {
	j = j + cnt + 1;
      }
      cnt = 0;
      if (j == i) {
	++ j;
      }
    }
  }
  // i is the index of minimum rotation
  Container res(n);
  std::copy(seq.begin() + i, seq.end(), res.begin());
  std::copy(seq.begin(), seq.begin() + i, res.begin() + n - i);
  return res;
}

int solution(const std::vector<std::vector<int>> &A, int P) {
  int n = A.size();
  auto clocks = A;
  for (auto& clock : clocks) {
    std::sort(clock.begin(), clock.end());
    int back = clock.back();
    std::adjacent_difference(clock.begin(), clock.end(), clock.begin());
    clock.front() = (clock.front() - back + P) % P;
    clock = lexicographcally_minimum_seq(clock);
  }
  std::sort(clocks.begin(), clocks.end());
  int pairs = 0;
  for (int i = 0, cnt = 0; i < n; ++i) {
    if (i > 0 && clocks[i] == clocks[i-1]) {
      ++ cnt;
      pairs += (cnt - 1);
    } else {
      cnt = 1;
    }
  }
  return pairs;
}
