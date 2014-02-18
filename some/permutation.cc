#include "vector"


// TODO
// write it with template
// algorithm
// chop off the last element, and permutate a[0,n-1)
// then insert a[n-1] into all the position of the permutated a[0,n-1) 
// But this seems space expensive

// Do it with the same array. Need to restore every time.

// The most easily understandable approach is to choose from candidates
// dfs(now, num) {
//   if (now == num.size()) return
//   for (i = now -> num.size()) {
//     swap(num[now], num[i])
//     dfs(now+1, num)
//     swap(num[now], num[i])
