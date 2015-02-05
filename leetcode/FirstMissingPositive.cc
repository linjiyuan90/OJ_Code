class Solution {
public:
  int firstMissingPositive(int a[], int n) {
    for (int i = 0; i < n; ++i) {
      while(a[i] > 0 && a[i] <= n && a[a[i]-1] != a[i]) {
	// put the right thing in the right place
	std::swap(a[a[i]-1], a[i]);
      }
    }
    int ans = n + 1;
    for (int i = 0; i < n; ++i) {
      if (a[i] != i + 1) {
	ans = i + 1;
	break;
      }
    }
    return ans;
  }
};
