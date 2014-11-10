#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

pair<int, int> maxVisit(const vector<vector<int>>& maze) {
  int S = maze.size();
  vector<pair<int, int>> valIndex;
  // index it
  for (int r = 0; r < S; ++r) {
    for (int c = 0; c < S; ++c) {
      valIndex.push_back({maze[r][c], r * S + c});
    }
  }
  sort(valIndex.begin(), valIndex.end(), greater<pair<int, int>>());
  vector<int> visitTimes(S * S, 1);
  for (auto& p : valIndex) {
    int v = p.first;
    int r = p.second / S, c = p.second % S;
    for (int k = 0; k < 4; ++k) {
      int rr = r + dx[k], cc = c + dy[k];
      if (rr < 0 || rr >= S || cc < 0 || cc >= S) {
        continue;
      }
      if (maze[rr][cc] == maze[r][c] + 1) {
        visitTimes[maze[r][c]] = visitTimes[maze[rr][cc]] + 1;
      }
    }
  }
  vector<int>::iterator it = max_element(visitTimes.begin(), visitTimes.end());
  return {it - visitTimes.begin(), *it};
}

int main() {
  int T, t = 1, S;
  for (cin >> T; T--; t++) {
    cout << "Case #" << t << ": ";
    cin >> S;
    vector<vector<int>> maze(S, vector<int>(S));
    for (auto& row : maze) {
      for (auto& col : row) {
        cin >> col;
        --col;
      }
    }
    pair<int, int> ans = maxVisit(maze);
    cout << ans.first + 1 << " " << ans.second << endl;
  }
  return 0;
}
