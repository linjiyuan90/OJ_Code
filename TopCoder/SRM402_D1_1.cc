/*
  Given a permutation, at aach step, randomly choose one pair that A[i] >  A[j] (i < j) and swap.
  Find the expectation of swaps.
  e = 1 + sum(e')*1/p, p is number of such pairs
*/

#include "vector"
#include "unordered_map"
#include "algorithm"
#include "numeric"
#include "functional"

class RandomSort {
public:
  int getPermutationHash(const std::vector<int>& permutation) {
    std::vector<int> rank(permutation.size());
    std::iota(rank.begin(), rank.end(), 1);
    int f = std::accumulate(rank.begin(), rank.end(), 1, std::multiplies<int>());
    int hash = 0;
    for (int i = 0, n = permutation.size(); i < n; ++i) {
      f /= (n-i);
      auto it = std::find(rank.begin(), rank.end(), permutation[i]);
      hash += (it - rank.begin()) * f;
      rank.erase(it);
    }
    return hash;
  }

  double getExpected(std::vector<int>& permutation) {
    static std::unordered_map<int, double> cache;
    int hash = getPermutationHash(permutation);
    if (cache.count(hash)) {
      return cache[hash];
    }
    double e = 0;
    int c = 0;
    // enumerate all inversion pairs
    for (int i = 0, n = permutation.size(); i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (permutation[i] > permutation[j]) {
          ++ c;
          std::swap(permutation[i], permutation[j]);
          e += getExpected(permutation);
          std::swap(permutation[i], permutation[j]);
        }
      }
    }
    if (c > 0) {
      e = e / c + 1;
    }
    return cache[hash] = e;
  }
};
