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


# DP
## bit/digit count problem
* gcj2014_R1B_B
* codility **NumberOfZeros**
```
count(i, less)
```
# knapback
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
      
