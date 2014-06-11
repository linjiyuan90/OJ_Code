//
//  OrienteeringDriver.cc
//  WAP_EX1
//
//  Created by Jiyuan, Lin (林基远) <linjijyuan90@gmail.com>

#include "iostream"
#include "algorithm"
#include "vector"
#include "queue"

#include "Orienteering.h"

int main(int argc, char* argv[]) {
  std::ios::sync_with_stdio(false);
  // clock_t start = clock();
  // other algorithm Orienteerings
  // PQOrienteering o;
  // BIOrienteering o;
  Orienteering o;
  o.main();
  // clock_t end = clock();
  // std::cerr << "Total time: " << ((double)(end - start) / CLOCKS_PER_SEC) << " seconds" << std::endl;
  return 0;
}

