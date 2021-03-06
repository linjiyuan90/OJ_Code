# Sequence
## Max sum
* variants: allow one swap; cycle
## Next Permutation
## Maximum Number of Concurrent events
* maintain current open event, EPI13.10
## auxiliary prefix_min, monotonic stack/deque
* max{j-i} where A[i] < A[j]
** a characteristic is that: **keep smaller and earlier A[i], larger and later A[j]**
** `O(nlogn)` solution is to maintain `prefix_min` then do a binary search
** `O(n)` solution is to maintain a `decreasing deque` to store A[i] (from left
    to right), a `decreasing stack` to store A[j] (from right to left).
* max{j-i} where A[j] - A[i] < k
* max{j-i}, where max{A[i..j]} - min{A[i..j]} < k
** maintain two `deque`, one **desc**, one **asc**; pop front until the fronts
    of two deques < k. Note, when poping, need to update second front's prefix index.

## swap permutation
* how many sequence can get after swap k adjacent/arbitratry pairs. hackerrank
  `swap permutation`
# String
## palindrome
* Manachor O(n)
```
int n = S.length(), m = 2*n+1;
std::string str(m, '#');
for (int i = 0; i < n; ++i) {
  str[2*i+1] = S[i];
}
std::vector<int> part(m);
for (int i = 0, C = 0, R = 0; i < m; ++i) {
  int ii = C - (i - C);
  part[i] = R > i ? std::min(part[ii], R - i) : 0;
  while (i+part[i]+1 < m
   && i-part[i]-1 >= 0
   && str[i+part[i]+1] == str[i-part[i]-1]) {
	++ part[i];
  }	 
  if (i+part[i] > R) {
	R = i+part[i];
	C = i;
  }
}
```
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
** a variant is to find the longest suffix of A that's prefix of B. Use the
  next, just change to compare with B.
```c++
// need to judge whether A is preffix of B first
// since next[n-1] + 1 < n
next[0] = -1;
for (int i = 1; i < n; ++i) {
  for (next[i] = next[i-1] + 1; next[i] != -1 && A[i] != B[next[i]]; ) {
    next[i] = next[i] == 0 ? -1 : next[next[i]-1] + 1;
  }
}
return next[n-1]+1;
```
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


## characteristic
* if a[0..m) == a[n-m..n), m > n/2,
  then a[0..k) == a[k..2k) == ..., k = n-m and k | n
# Graph
## traversal
* normally, `mark[v]` means (start from s), v has been visited; note it's
  **started from s**. See
  https://code.google.com/codejam/contest/3214486/dashboard#s=p2 to impress the understanding.
* `mark[(u, v)]` the edge has been vistied (start from what?)
### no reursive traversal with stack
* binary tree preorder just pop and push children
* binary tree inorder pop, and before push children, check whether last pointer
  is its left child. if not, push right, root and left.
* binary tree postorder how? need some flags. With respect to the first visit,
  no need to pop, just push.
* what about graph preorder traversal?

# Tree
## longest path
* variants


## record children's state to their ancestors, EPI 9.4
## travesal
* record prev traversed node
## binary search tree
* iterator, next()
## tree dp
* way of cut tree into k parts, define state that u is separate from its parent
  or not. `connect[u][k],
  cut[u][k]`. https://www.hackerrank.com/challenges/cuttree
## cut the tree into forest
* hackerank Kundu and Tree. Cut the tree into serveral components, then counting.
# DP
## bit/digit count problem
* gcj2014_R1B_B
* codility **NumberOfZeros**
```
count(i, less)
```
### two ways
* general framework
* iterative, specific to problem

## knapback
* 0-1
* items with specific number
** no value, just availability, codility MinAbsSum, nice transformation, O(SUM*N)
```
// when at item a, dp[j] means
// dp[j] = -1, unfeasible
// dp[j] >= 0, feasible, and there are dp[j] item a can be used.
dp[0] = 0;
for ({a, count} : items) {
  if (count > 0) {
    for (int j = 0; j <= S; ++j) {
	  if (dp[j] >= 0) dp[j] = count;
	  else if (j >= a && dp[j-a] > 0) dp[j] = dp[j-a] - 1;
    }
  }
}
```
** with value, it seems requires O(SUM*N*C)

## k large
* hackerrank "Extremum Permutations", record how larage current P[i] is, or say,
  how many numbers that are less than P[i] in the left numbers after making
  [1..i] legal. `dp[i][lt]`
# Bitwise
## number appearance
* find the only element which occures once while others occure three times,
  leetcode SingleNumber2. think it as ternary, use two variable to record each
  bit's count (1 or 2)
* http://zhedahht.blog.163.com/blog/static/2541117420071128950682/
* http://zhedahht.blog.163.com/blog/static/25411174201283084246412/
## some
* lowbit `x & -x`, submask `(x-1) & ALL`
* use `&&` as `if`, `(clausea) && (clauseb)`
# Recursion
## basic
* multiply, divide, pow
## some nice problems
* gcj2014_R1B_B
* gcj_campus2014_RA_B
# probability & expectation
* the expectation of seeing an event of probability p is
```
x = p + (1-p)(1+x)
x = 1/p
```
* sequence, consider suffix, e.g., "expection steps to get two heads during
  trials"
[tutorial-expection](http://www.codechef.com/wiki/tutorial-expectation)
```
1) first flip is a tail, then we waste one flip, p is 0.5
2) first two flips are head, tail, then we waste twon flips, p is 0.25
2) first two flips are heads, then we're done, p is 0.25
x = 0.5 * (1 + x) + 0.25 * (x + 2) + 0.25 * 2
```
** this looks like a state machine, store the temporary possible paths, `11..1?`
* find the formula of `expectation` seems a shortcut! Otherwise, need to find a
  series formula!
* `linearity of expectation` seems so important, but I still don't understand.
  It doesn't require variable to be independent.
** CF280C
* expected number of trials to see 6 dices value, EPI 20.12
* probablity to form a triangle
# Combination
* form n balls from k groups, `C(n+k-1, n)`. That's, `n1+n2+..+nk=n`, there are
  n+k-1 positions (each ni and '+')
* insert k new balls to existing n-k balls to form a seq, `C(n, k)`. That's
  choosing k position from final n positions for k new balls.
# Segment Tree
* TODO. with respect to float number, map to int, and the segment becomes [l, m], [m, r]
# cycle
* arrange `a1 a2.. an b1 b2.. bn` to `a1 b1 a2 b2 ...`; note the cycle
```
x = x*2 - 1, if x <= n;
x = (x-n)*2, if x > n.
but need something to mark visited position. store at the high bit?
```
# other
## parenthese
* valid parentheses, 2 situations
  (….)(...), (….)
* count parentheses, enumerate the which ‘)’ to match the first ‘(‘
  ()…, (())…, (…)...
## union of rectangle
* a common strategy is to scan x from left to right, insert segments of this x.
  Segment has two possible state, open/closed. Then consider the strip between
  adjacent x. `Segment Tree` can be used to store the segments. +1 when
  encounter an open segment, and -1 when encouner a closed segment.
