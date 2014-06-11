//
//  Orienteering.cc
//  WAP_EX1
//
//  Created by Jiyuan, Lin (林基远) <linjijyuan90@gmail.com>

#include "iostream"
#include "algorithm"
#include "vector"
#include "queue"

#include "Orienteering.h"

////////////////////////////////////////////////////////////////////////////////
// Implementation of Orienteering

void Orienteering::main() {
  while(!std::cin.eof() && map.read()) {
    if (!map.isValid() ||
        map.n < MIN_N ||
        map.m < MIN_M ||
        map.n > MAX_N ||
        map.m > MAX_M ||
        map.numCheckPoints() > MAX_NUM_CHECK_POINTS ||
        !map.calcShortestPath()) {
      std::cout << -1 << std::endl;
      continue;
    }
    calcOneZero(map.numCheckPoints());
    std::cout << calc() << std::endl;
  }
}

// Extract ones and zeros from each mask, continue from last maxK
void Orienteering::calcOneZero(int nextK) {
  if (nextK <= maxK) {
    return;
  }
  int ALL_MASK = (1 << nextK) - 1;
  ones.resize(ALL_MASK + 1);
  zeros.resize(ALL_MASK + 1);
  for (int mask = (1 << maxK); mask <= ALL_MASK; ++mask) {
    for (int k = 0, mk = 1; k < MAX_NUM_CHECK_POINTS; ++k, mk <<= 1) {
      if (mask & mk) {
        ones[mask].push_back(k);
      } else {
        zeros[mask].push_back(k);
      }
    }
  }
  maxK = nextK;
}

// Naive dp O(K^2*2^K)
// After calculating shortest path between points ('@', 'S', 'G') 
// in OrienteeringMap, do a dp on this points.
// dp[mask][k]: the min cost start from S to k after gathering mask
// The next step will choose a k', which not in mask, then transfer to it from k
// that's (mask, k) => (mask|(1 << k'), k')
// The calculation can be done by iterating mask from less 1s to more 1s, 
// and then for each mask, iterating k(1s in mask) and iterating k'(0s in mask).
int Orienteering::calc() {
  int K = map.numCheckPoints(), S = map.getS(), G = map.getG();
  if (K == 0) {
    return map.dist(S, G);
  }
  // init
  int ALL_MASK = (1 << K) - 1;
  dp.resize(ALL_MASK + 1);
  for (int mask = 0; mask <= ALL_MASK; ++mask) {
    dp[mask].assign(K, INT_MAX);
  } 
  
  // local variable is much faster
  std::vector<std::vector<int>> dist = map.getDists();

  for (int k = 0, mk = 1; k < K; ++k, mk <<= 1) {
    dp[mk][k] = map.dist(S, k);
  }
  for (int mask = 1; mask <= ALL_MASK; ++mask) {
    for (int &kk : zeros[mask]) {
      if (kk >= K) {
        break;
      }
      int min_dist = dp[mask|(1 << kk)][kk];
      for (int &k : ones[mask]) {
        min_dist = std::min(min_dist, dp[mask][k] + dist[k][kk]);
      }
      dp[mask|(1 << kk)][kk] = min_dist;
    }
  }
  int ans = INT_MAX;
  for (int k = 0; k < K; ++k) {
    ans = std::min(ans, dp[ALL_MASK][k] + dist[k][G]);
  }
  return ans;
}

////////////////////////////////////////////////////////////////////////////////
// Implementation of BIOrienteering

// Naive dp above have time complexity O(K^2*2^K)
// In theory, this complexity can be reduced to O(K^2*2^(K/2))
// by calculating from both S and G to a middle/common mask.
// The middle mask is mask with (K/2 + 1) 1s, so only 2^(K/2) masks need to be 
// calculated, which is much less than whole masks(2^K).
// Finally, find the min{dp[mask][k] + rdp[_mask | (1 << k)][k]}
// where mask has (K/2 + 1) 1s and k is the 1s in mask, _mask = ALL_MASK ^ mask.
// However, in my test, this algorithm is slower than naive dp.
// I think this can be blamed to extra cost of accessing one more array.
int BIOrienteering::calc() {
  int K = map.numCheckPoints(), S = map.getS(), G = map.getG();
  if (K == 0) {
    return map.dist(S, G);
  }
  // init
  int ALL_MASK = (1 << K) - 1;
  dp.resize(ALL_MASK + 1);
  rdp.resize(ALL_MASK + 1);
  for (int mask = 0; mask <= ALL_MASK; ++mask) {
    dp[mask].assign(K, INT_MAX);
    rdp[mask].assign(K, INT_MAX);
  }

  // local variable is much faster
  std::vector<std::vector<int>> dist = map.getDists();

  for (int k = 0, mk = 1; k < K; ++k, mk <<= 1) {
    dp[mk][k] = dist[S][k];
    rdp[mk][k] = dist[k][G];
  }
  int half_K = K / 2;
  std::vector<int> half_masks;
  for (int mask = 1; mask <= ALL_MASK; ++mask) {
    if (ones[mask].size() == half_K + 1) {
      half_masks.push_back(mask);
    }
    if (ones[mask].size() > half_K) {
      continue;
    }
    for (int &kk : zeros[mask]) {
      if (kk >= K) {
	break;
      }
      int _mask = mask | (1 << kk);
      int min_dist = dp[_mask][kk];
      int min_rdist = rdp[_mask][kk];
      for (int &k : ones[mask]) {
	min_dist = std::min(min_dist, dp[mask][k] + dist[k][kk]);
	min_rdist = std::min(min_rdist, rdp[mask][k] + dist[k][kk]);
      }
      dp[_mask][kk] = min_dist;
      rdp[_mask][kk] = min_rdist;
    }
  }
  int ans = INT_MAX;
  for (int &mask : half_masks) {
    int _mask = ALL_MASK ^ mask;
    for (int &k : ones[mask]) {
      ans = std::min(ans, dp[mask][k] + rdp[_mask | (1 << k)][k]);
    }
  }
  return ans;
}

////////////////////////////////////////////////////////////////////////////////
// Implementation of PQOrienteering

// Think (mask, k) as a node in a graph, then this problem is to find a shortest
// path from (0, S) to (ALL_MASK, G), while the edge weight between (mask, k)
// and (mask|(1 << k'), k') is dist[k][k']
// Any SSSP(Single-Source Shortest-Path) algorithm will solve it.
// Here, I use priority_queue.
// At each time, take node with min cost from pq, if it hasn't been calculated,
// use it to relax its neighbor nodes and push to pq.
// Do this until reach (ALL_MASK, G).
// Time Complexity O(2^K*K*log(2^K*K)*K) = O(2^K*K^2*(K+ logK))
int PQOrienteering::calc() {
  int K = map.numCheckPoints(), S = map.getS(), G = map.getG();
  if (K == 0) {
    return map.dist(S, G);
  }
  // Node is used to store  (-cost, (mask, k))
  // -cost since by default priority_queue is greater first
  std::priority_queue<Node> pq;
  int ALL_MASK = (1 << K) - 1;
  dp.resize(ALL_MASK + 1);
  for (int mask = 0; mask <= ALL_MASK; ++mask) {
    dp[mask].assign(K, INT_MAX);
  }
  
   // local variable is much faster
  std::vector<std::vector<int>> dist = map.getDists();

  for (int k = 0, mk = 1; k < K; ++k, mk <<= 1) {
    dp[mk][k] = dist[S][k] + dist[k][G];
    pq.push({-dp[mk][k], {mk, k}});
  }
  while(!pq.empty()) {
    Node top = pq.top();
    pq.pop();
    int d = -top.first;
    int mask = top.second.first;
    int k = top.second.second;
    if (d > dp[mask][k]) {
      continue;
    }
    if (mask == ALL_MASK) {
      return d;
    }
    for (int &kk : zeros[mask]) {
      if (kk >= K) {
	continue;
      }
      int _mask = mask | (1 << kk);
      int _d = d - dist[k][G] + dist[k][kk] + dist[kk][G];
      if (dp[_mask][kk] > _d) {
	dp[_mask][kk] = _d;
	pq.push({-dp[_mask][kk], {_mask, kk}});
      }
    }
  }
  return -1;
}
