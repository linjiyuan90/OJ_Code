#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool checkContinous(int mask) {
  while (mask > 0) {
    if ((mask&3) == 3) {
      return false;
    }
    mask >>= 1;
  }
  return true;
}

int getRowSum(const vector<int>& row, int mask) {
  int sum = 0;
  for (int i = 0; mask > 0; ++i) {
    if (mask & 1) {
      sum += row[i];
    }
    mask >>= 1;
  }
  return sum;
}

int getMaxSum(const vector< vector<int> >& grid) {
  int n = grid.size();
  int AllMask = (1 << n) - 1;
  vector< vector<int> > sum(2, vector<int>(AllMask + 1));
  int now = 0, next = 1;
  for (int r = 0; r < n; ++r) {
    fill(sum[next].begin(), sum[next].end(), 0);
    for (int mask = 0; mask <= AllMask; ++mask) {
      if (!checkContinous(mask)) {
        continue;
      }
      sum[next][mask] = sum[now][AllMask ^ mask] + getRowSum(grid[r], mask);
    }
    // let sum[next][mask] stores max sum of mask's sub mask
    for (int mask = 0; mask <= AllMask; ++mask) {
      for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) {
          sum[next][mask] = max(sum[next][mask], sum[next][mask ^ (1 << i)]);
        }
      }
    }
    swap(now, next);
  }
  return sum[now][AllMask];
}

int main() {
  for (int n; cin >> n; ) {
    vector< vector<int> > grid(n, vector<int>(n));
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        cin >> grid[r][c];
      }
    }
    cout << getMaxSum(grid) << endl;
  }
  return 0;
}
