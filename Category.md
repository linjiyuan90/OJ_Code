# Sequence
## Max sum
* variants: allow one swap; cycle
## Next Permutation
## Maximum Number of Concurrent events
* maintain current open event, EPI13.10

# String
## Lexicographically Minimum String Rotation
```
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
```
## KMP
* common senses:
  S[i-next[i]..i] = S[0..next[i]]
* several i may have same next[i], next[] form a tree (so i and i' can have a
  common ancestor)
* repeat string
* O(n) to count the occurrences of all prefix (Codility, PrefixMaxProduct)
```c++
for (int i = n - 1; i >= 0; --i) {
  ++ cnt[i];
  if (next[i] != -1) {
    cnt[next[i]] += cnt[i];  // S[0..i] is also an occurence of S[0..next[i]]
  }
}
```
### Extend KMP


# Graph

# Tree
## longest path
* variants


# DP
# knapback
* 0-1
* items with specific number
** no value, just availability, codility MinAbsSum, nice transformation, O(SUM*N)
```

```
** with value, it seems requires O(SUM*N*C)
