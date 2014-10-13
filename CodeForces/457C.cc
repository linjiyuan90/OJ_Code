/*
  Bribe some voters to make candidate 0 has max votes.
  At the same time, minimize the cost.

  A greedy approach which bribes the minimial voters each time seems not correct.
  
  **Enumerate the bound** which other candidates' votes must below it.
  The cost according to the bound is decreasing first then increase.
  So, using **Ternary Search**!

  Another solution is:
  At first, bribe all the voters, then decrease the bound.
  At each bound, put back the expensive one till candidates0 has bound votes.
  If after put back, some other candidates has votes >= bound, need to 
  re bribe those voters.
  The code of 7434760 Gonens is cool. But I stil can't master it.
*/

#include "set"
#include "numeric"
#include "tuple"
#include "unordered_map"
#include "iostream"
#include "vector"
#include "string"
#include "stdexcept"
#include "string"
#include "algorithm"

struct Voter {
  Voter() {}
  Voter(int cand, int cost): candidate(cand), cost(cost) {
  }
  int candidate;
  int cost;
  bool operator < (const Voter& that) const {
    return cost < that.cost || (cost == that.cost && candidate < that.candidate);
  }
};

namespace TernarySearch {
  int calculate(const std::vector<Voter> voters, int bound) {
    std::unordered_map<int, int> votes;
    for (auto& voter : voters) {
      ++votes[voter.candidate];
    }
    int n = voters.size();
    int cost = 0;
    std::vector<bool> used(voters.size());
    std::transform(voters.begin(),
                   voters.end(),
                   used.begin(),
                   [](const Voter& voter) {
                     return voter.candidate == 0;
                   });
    for (int i = 0; i < n; ++i) {
      if (!used[i] && votes[voters[i].candidate] >= bound) {
        used[i] = true;
        --votes[voters[i].candidate];
        ++votes[0];
        cost += voters[i].cost;
      }
    }
    for (int i = 0; i < n && votes[0] < bound; ++i) {
      if (!used[i]) {
        used[i] = true;
        ++votes[0];
        cost += voters[i].cost;
      }
    }
    return votes[0] < bound ? std::numeric_limits<int>::max() : cost;
  }
  
  int minCost(std::vector<Voter> voters) {
    std::sort(voters.begin(), voters.end());
    int lo = 0, hi = voters.size();
    while (lo < hi) {
      int d = (hi-lo)/3;
      int m1 = lo + d, m2 = hi - d;
      if (calculate(voters, m1) < calculate(voters, m2)) {
        hi = m2-1;
      } else {
        lo = m1+1;
      }
    }
    return calculate(voters, lo);
  }
};

int main() {
  for (int n; std::cin >> n; ) {
    std::vector<Voter> voters(n);
    for (auto& voter : voters) {
      std::cin >> voter.candidate >> voter.cost;
    }
    std::cout << TernarySearch::minCost(voters) << std::endl;
  }
  return 0;
}
