//
//  Orienteering.h
//  WAP_EX1
//
//  Created by Jiyuan, Lin (林基远) <linjijyuan90@gmail.com>

#ifndef WAP_EX1_ORIENTEERING_H_
#define WAP_EX1_ORIENTEERING_H_

#include "OrienteeringUtil.h"

// constants
const int MAX_NUM_CHECK_POINTS = 18;
const int MIN_N = 1;
const int MIN_M = 1;
const int MAX_N = 100;
const int MAX_M = 100;

class Orienteering {
 protected:
 
  // dp[mask][k]: 
  // the min cost start from S to k after gathering checkPoints(represented by mask)
  std::vector<std::vector<int>> dp;
  // ones[mask] stores which bit of mask is 1, zeros is analogous.
  // e.g, ones[22]: {1, 2, 4}, zeros[22]: {0, 3, 5, 6, ..., MAX_NUM_CHECK_POINTS - 1}
  std::vector<std::vector<int>> ones;
  std::vector<std::vector<int>> zeros;

  int maxK = 0;

  // delegate graph related operations to OrienteeringMap
  OrienteeringMap map;

  void calcOneZero(int k);
  virtual int calc();

public:
  void main();
};

class BIOrienteering : public Orienteering {
  // rdp is analogous to dp, while starting from G
  std::vector<std::vector<int>> rdp;
 protected:
  int calc();
};

class PQOrienteering : public Orienteering {
  typedef std::pair<int, std::pair<int, int>> Node;
 protected:
  int calc();
};

#endif // WAP_EX1_ORIENTEERING_H_
