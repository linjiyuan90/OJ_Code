class Solution {
public:
  int numTrees(int n) {
    vector<int> ways(n+1);
    ways[0] = 1;
    for (int i = 1; i <= n; ++i) {
      for (int r = 1; r <= i; ++r) {
        ways[i] += ways[r-1] * ways[i-r];
      }
    }
    return ways[n];
  }
};
