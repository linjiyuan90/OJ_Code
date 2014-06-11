//
//  OrienteeringUtil.cc
//  WAP_EX1
//
//  Created by Jiyuan, Lin (林基远) <linjijyuan90@gmail.com>

#include "vector"
#include "iostream"
#include "string"
#include "queue"
#include "stdexcept"
#include "initializer_list"

#include "OrienteeringUtil.h"

////////////////////////////////////////////////////////////////////////////////
// Implementation of Point

// assign with initilizer_list, e.g. Point p = {1, 2};
Point& Point::operator = (std::initializer_list<int> xy) {
  if (xy.size() != 2) {
    throw std::invalid_argument("Point should be assigned as {x, y}");
  }
  x = *xy.begin();
  y = *(xy.begin()+1);
  return *this;
}
Point& Point::operator = (const Point &that) {
  x = that.x;
  y = that.y;
  return *this;
}

bool Point::operator < (const Point &that) const {
  return x < that.x || (x == that.x && y < that.y);
}
bool Point::operator == (const Point &that) const {
  return x == that.x && y == that.y;
}
bool Point::operator != (const Point &that) const {
  return !(*this == that);
}

std::ostream& operator<<(std::ostream &os, const Point &p) {
  os << "(" << p.x << "," << p.y << ")";
  return os;
}

////////////////////////////////////////////////////////////////////////////////
// Implementation of OrienteeringMap

// clear the data for reuse
void OrienteeringMap::init() {
  checkPoints.clear();
  _isValid = true;
  S = INVALID_POINT;
  G = INVALID_POINT;
}

// Read and record S, G, checkPoints
// return false if read failed
bool OrienteeringMap::read() {
  init();
  std::cin >> m >> n;
  if (!std::cin) {
    return false;
  }
  map.resize(n);
  for (int i = 0; i < n; ++i) {
    // getline();
    std::cin >> map[i];
    if (map[i].size() != m) {
      _isValid = false;
      continue;
    }
    for (int j = 0; j < m; ++j) {
      if (map[i][j] == 'S') {
	// have more than one 'S'? OK, mark it invalid
	if (S != INVALID_POINT) {
	  _isValid = false;
	}
	S = {i, j};
      } else if (map[i][j] == 'G') {
	// have more than one 'G'? OK, mark it invalid
	if (G != INVALID_POINT) {
	  _isValid = false;
	}
	G = {i, j};
      } else if (map[i][j] == '@'){
	checkPoints.push_back(Point(i, j));
      } else if (map[i][j] != '.' && map[i][j] != '#') {
	// contain other elments? OK, mark it invalid
	_isValid = false;
      }
    }
  }
  // append S, G to the checkPoints for convenient process
  checkPoints.push_back(S);
  checkPoints.push_back(G);
  return true;
}

// Calculate the shortest distance between '@', 'S', 'G' using bfs
// if some points can't be reached, return false
bool OrienteeringMap::calcShortestPath() {
  int K = numCheckPoints();
  dists.resize(K + 2);
  // for every point in '@', and 'S', 'G', start from it and bfs
  for (int k = 0; k < K + 2; ++k) {
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, INT_MAX));
    const Point &p = checkPoints[k];
    dist[p.x][p.y] = 0;
    std::queue<Point> Q;
    Q.emplace(p);
    while(!Q.empty()) {
      const Point &p = Q.front();
      Point pp = p;
      for (int j = 0; j < 4; ++j) {
	pp = {p.x + dx[j], p.y + dy[j]};
	// valid and haven't been visited yet
	if (isValid(pp.x, pp.y) && dist[pp.x][pp.y] == INT_MAX) {
	  Q.emplace(pp);
	  dist[pp.x][pp.y] = dist[p.x][p.y] + 1;
	}
      }
      Q.pop();
    }
    dists[k].resize(K + 2);
    // store shortest distance from k to other point kk
    for (int kk = 0; kk < K + 2; ++kk) {
      const Point &p = checkPoints[kk];
      // if '@', 'S', 'G' are not connected, return false
      if (dist[p.x][p.y] == INT_MAX) {
	return false;
      }
      dists[k][kk] = dist[p.x][p.y];
    }
  }
  return true;
}

int OrienteeringMap::numCheckPoints() {
  return std::max(0, (int)checkPoints.size() - 2);
}

int OrienteeringMap::getS() {
  return numCheckPoints();
}
int OrienteeringMap::getG() {
  return numCheckPoints() + 1;
}
const Point& OrienteeringMap::getSPoint() {
  return checkPoints[numCheckPoints()];
}
const Point& OrienteeringMap::getGPoint() {
  return checkPoints.back();
}
const Point& OrienteeringMap::getPoint(int k) {
  if (k < 0 || k >= checkPoints.size()) {
    std::string msg = "Wrong point index: " + std::to_string(k);
    throw std::range_error(msg);
  }
  return checkPoints[k];
}

// check whether (x, y) in map and is able to go
bool OrienteeringMap::isValid(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m && map[x][y] != '#';
}

// check whether the map is valid:
// 1) only one S and G
// 2) map only consists of 'S', '@', 'G', '.', '#'
bool OrienteeringMap::isValid() {
  return _isValid && S != INVALID_POINT && G != INVALID_POINT;
}

// shortest dist between checkPoints[a] and checkPoints[b]
int OrienteeringMap::dist(int a, int b) {
  if (a < 0 || a > numCheckPoints() + 2 ||
      b < 0 || b > numCheckPoints() + 2) {
    std::string msg = "Wrong point index: (" + std::to_string(a) + ", " +
      std::to_string(b) + ")";
    throw std::range_error(msg);
    }
  return dists[a][b];
}

// return the whole shortest distance
std::vector<std::vector<int>> OrienteeringMap::getDists() {
  return dists;
}
