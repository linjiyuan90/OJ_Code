//
//  OrienteeringUtil.h
//  WAP_EX1
//
//  Created by Jiyuan, Lin (林基远) <linjijyuan90@gmail.com>

#ifndef WAP_EX1_ORIENTEERING_UTIL_H_
#define WAP_EX1_ORIENTEERING_UTIL_H_

#include "limits.h"

#include "vector"
#include "iostream"
#include "string"
#include "initializer_list"

// Directions of next step, that's (x, y) => (x + dx[j], y + dy[j])
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

class Point {
 public:
  int x, y;
  Point() {}
  Point(int x, int y): x(x), y(y) {}

  Point& operator = (std::initializer_list<int> xy);
  Point& operator = (const Point &that);
  bool operator < (const Point &that) const;
  bool operator == (const Point &that) const;
  bool operator != (const Point &that) const;
  friend std::ostream& operator<<(std::ostream &os, const Point &p);
};

const Point INVALID_POINT(INT_MIN, INT_MIN);

// class OrienteeringMap
// main functions:
//  1) read data and check
//  2) calculate shortest path
class OrienteeringMap {

  // record every point of the map
  std::vector<std::string> map;
  Point S, G;
  // S, G will be appended back
  std::vector<Point> checkPoints;
  // store shortest path between pair of '@', 'S', 'G'
  std::vector<std::vector<int>> dists;
  // whether the map is valid
  bool _isValid;

 public:  
  int n, m;

  // clear the data for reuse
  void init();

  // Read and record S, G, checkPoints
  // return false if read failed
  bool read();

  // Calculate the shortest distance between '@', 'S', 'G' using bfs
  // if some points can't be reached, return false
  bool calcShortestPath();

  int numCheckPoints();

  int getS();
  int getG();
  const Point &getSPoint();
  const Point &getGPoint();
  const Point &getPoint(int k);
  
  // check whether (x, y) in map and is able to go
  bool isValid(int x, int y);

  // check whether the map is valid:
  // 1) only one S and G
  // 2) map only consists of 'S', '@', 'G', '.', '#'
  bool isValid();

  // shortest dist between checkPoints[a] and checkPoints[b]
  int dist(int a, int b);
  // return the whole shortest distance
  std::vector<std::vector<int>> getDists();
};

#endif // WAP_EX1_ORIENTEERING_UTIL_H_
