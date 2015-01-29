/*
  Given a set of nodes, each has a weight, calculate the ways of generating a huffman tree.
  
  One counting pattern is: ∏wi! * #structure
  But, #sturcture seems complicated to count.
  
  apaidu has a nice counting pattern: http://hihocoder.com/contest/challenge7/solution/245101
  He is recording: ways of different set that generated from a set of even num nodes which have same weight.
  Note, is ways of different set, not sequence!!!
  ways[n] = ways[n-2] * (n-1) * 2, n is even
  The explanation is: when calculating ways[n], for nth node, choose one to combine, that's (n-1) candidates 
  and 2 combine ways (left or right). And the left n-2 nodes is ways[n-2].
  From a combinatorics aspect, ways[n] = n!/(n/2)!

  I think the more generated problem is: ways of merging a set of nodes into one node.

  To sum up: record ways of a set instead of sequence or something else!!!
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

const int64_t Mod = 1000000007;
const int MaxN = 1000000;

namespace HuffmanWays {

vector<int64_t> ways(MaxN + 1);

void init() {
  ways[0] = 1;
  for (int n = 2; n <= MaxN; n += 2) {
    ways[n] = ways[n-2] * (n-1) * 2 % Mod;
  }
}

int calcWays(const vector<int>& w) {
  int n = w.size();
  map<int64_t, int> cnt;
  for (int i = 0; i < n; ++i) {
    ++cnt[w[i]];
  }
  int64_t ans = 1;
  for (int m = n; m > 1; ) {
    map<int64_t, int>::iterator it = cnt.begin();
    const int64_t& w = it->first;
    int& c = it->second;
    if (c % 2 == 0) {
      ans = ans * ways[c] % Mod;
      m -= c/2;
      cnt[w*2] += c/2;
      cnt.erase(it);
    } else {
      if (c > 1) {
        ans = ans * ways[c-1] % Mod * c % Mod;
        m -= c/2;
        cnt[w*2] += c/2;
      }
      cnt.erase(it);
      it = cnt.begin();
      const int64_t& w2 = it->first;
      int& c2 = it->second;
      ans = ans * c2 * 2 % Mod;
      --m;
      ++cnt[w + w2];
      if (--c2 == 0) {
        cnt.erase(it);
      }
    }
  }
  return ans;
}

}

int main() {
  ios::sync_with_stdio(false);
  HuffmanWays::init();
  int T, n;
  vector<int> w;
  for (cin >> T; T--;) {
    cin >> n;
    w.resize(n);
    for (int i = 0; i < n; ++i) {
      cin >> w[i];
    }
    cout << HuffmanWays::calcWays(w) << endl;
  }
  return 0;
}
