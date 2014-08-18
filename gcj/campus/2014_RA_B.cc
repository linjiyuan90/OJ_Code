/*
  id(x, y) = id(x', y') * 2 + (x > y)
  1) x' = x - y, y' = y
  2) x' = x, y' = y - x

  let x = 2^i + j + 1, 0 <= i, 0 <= j < 2^i
  f(i, j) = f(i-1, j) + f(i-1, j), j is even
*/

#include "iostream"

int main() {
  
  return 0;
}
