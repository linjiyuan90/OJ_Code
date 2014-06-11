# Statement
This is a file describing solution of ex1 by Jiyuan, Lin(林基远).
If you have any question, please feel free to contact me: linjiyuan90@gmail.com.

# Exam 1
I come out three algorithms for this problem.
## Algorithm1: Naive dp, Time O(k^2*2^K + (K+2)*n*m), Space O(2^K * K)
* The problem can be solved by dynamic programming, with state defining
  as`dp[mask][k]` meaning the `the minimum cost start from S and end at kth '@'
  gathering mask '@'`. The one-bit in `mask` represents the '@' has
  gathered. Then the final result will be `min(dp[mask][k] + dists[k][G])` while
  `dists[k][G]` is the shortest distance between kth '@' to G. The shortest
  distances between points can be calculated by BFS.
* time complexity `O(K^2*2^K + (K+2)*n*m)`, K is the number of check points
* pesudo code
```
let K = #{'@'s}
For each point p in { 'S', '@'s, 'G'}:
  bfs start from p, calculate shortest distance from p to {'S', '@'s, 'G'}, stored es dists[p][p']
For k <- 0 until K
  dp[1<<k][k] = dists[S][k]
For mask <- 1 until (1<<K)
  For k <- 0 until K
    if mask & (1<<k)
	  For k' <- 0 until K
	    if !(mask & (1<<k'))
		  dp[mask|(1<<k')][k'] = min(dp[mask|(1 << k')][k'], dp[mask][k] + dists[k][k'])
return min(dp[(1<<K)-1][k] + dists[k][G]), for k <- 0 until K
```

## Algorithm2: Bidirectional dp, Time O(k^2*2^(K/2) + (K+2)*n*m), Space O(2^K * K)
* The above dp can be improved by calculating from both S and G to a
  middle/common mask (**bidirectional**). The middle mask is mask with (K/2 + 1)
  1s, so only 2^(K/2) masks need to be calculated, which is much less than whole
  masks(2^K). Finally, find the min{dp[mask][k] + rdp[_mask | (1 << k)][k]},
  where mask has (K/2 + 1) 1s and k is the 1s in mask, _mask = ALL_MASK ^ mask.
* However, in my test, this algorithm is slower than naive dp. I think this can
  be blamed to extra cost of accessing one more array.

## Algorithm3:  Search using priority_queue, Time O(2^K*K^2*(K+ logK) + (K+2)*n*m), Space O(2^K * K)
* Think (mask, k) as a node in a graph, then this problem is to find a shortest
  path from (0, S) to (ALL_MASK, G), while the edge weight between (mask, k) and
  (mask|(1 << k'), k') is dist[k][k'] Any `SSSP(Single-Source Shortest-Path)`
  algorithm will solve it. Here, I use `priority_queue`.
* At each time, take node with min cost from pq, if it hasn't been calculated,
  use it to relax its neighbor nodes and push to pq.Do this until reach
  (ALL_MASK, G).
  
## run
To run it, please enter ex1 directory, the directory structure is:
```
$ tree
├── Makefile
├── Orienteering
├── data
│   ├── large.ans
│   ├── large.in
│   ├── sample.ans
│   ├── sample.in
│   ├── small.ans
│   └── small.in
└── src
    ├── Orienteering.cc
    ├── Orienteering.h
    ├── OrienteeringDriver.cc
    ├── OrienteeringUtil.cc
    └── OrienteeringUtil.h
```
Then make it and run:
```shell
$ make
$ time ./Orienteering < data/sample.in > data/sample.out
$ diff data/sample.out data/sample.ans
```

## File & Class descriptions
* Orienteering.cc, the main implementations of the three algorithms;
* OrienteeringUtil.cc, implement the utility functions and classes;
* OrienteeringDriver.cc, driver code to call Orienteering. To switch different
  algorithm, change to specific class.
* OrienteeringMap, which reads data, check validity and calculate shortest path;
* BIOrienteering, extends Orienteering, which implements the Bidirectional dp;
* PQOrienteering, extends Orienteering, which search the answer using
  priority_queue.

## Test Data,  Environment & Result
* The test data is provided by my classmate which generate them both randomly
  and manually. The answer of the small scale data are check manually, while
  data with large scale are check by comparing results between different
  classmates.
* Environment
	* OS: OS X 10.9.3
	* Hardware: 2.4 GHz i7, 8 GB 1600 MHz DDR3
	* Compiler: Clang-500.2.79
* Result
	* small.in takes 0.09s
	* large.in takes 5.48s 
