#include "algorithm"
#include "iostream"
#include "vector"

using namespace std;

class Solution {
public:
  int maximalRectangle(vector<vector<char> > &matrix) {
    if (matrix.empty()) {
      return 0;
    }
    int ans = 0;
    int n = matrix.size(), m = matrix[0].size();
    // enumerate two rows
    for (int i = 0; i < n; ++i) {
      vector<int> last_one(m, i-1);
      for (int j = i; j < n; ++j) {
	for (int k = 0; k < m; k++) {
	  if (matrix[j][k] == '1' && last_one[k] == j - 1) {
	    last_one[k] = j;
	  }
	}
	// use left, right pointer to check
	int l = 0, r = 0;
	while(r < m) {
	  if (l > r) {
	    ++ r;
	  } else if (last_one[l] != j) {
	    ++ l;
	  } else if (last_one[r] == j) {
	    ans = max(ans, (j - i + 1) * (r - l + 1));
	    ++ r;
	  } else { // last_one[r] != j
	    l = ++ r;
	  }
	}
      }
    }
    return ans;
  }
};
