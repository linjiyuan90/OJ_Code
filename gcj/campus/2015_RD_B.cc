#include <cassert>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
  int T, t = 1, n, p;
  for (cin >> T; T--; t++) {
    cout << "Case " << t << ": ";
    cin >> n;
    vector<pair<int, int>> bus(n);
    for (auto& b : bus) {
      cin >> b.first >> b.second;
    }
    cin >> p;
    for (int i = 0, x; i < p; ++i) {
      if (i > 0) {
        cout << " ";
      }
      cin >> x;
      cout << count_if(bus.begin(), bus.end(), [&x](const pair<int, int>& b) {
          return (b.first <= x && x <= b.second) ||
            (b.first >= x && x >= b.second);
        });
    }
    cout << endl;
  }
  return 0;
}
