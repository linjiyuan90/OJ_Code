class Solution {
public:
  void nextPermutation(vector<int> &num) {
    if (num.empty()) {
      return;
    }
    size_t i, j, n = num.size();
    for (i = n - 1; i > 0 && num[i-1] >= num[i]; i--) {
      // from right to left
      // find first i that has property:
      // num[i, n) is nonincreasing
      // num[i-1] < num[i]
    }
    if (i > 0) {
      for (j = n - 1; j > i && num[i-1] >= num[j]; j--) {
	// find num[j]
	// where num[j] is the minimum number > num[i], j in [i, n)
      }
      // swap(num[i-1], num[j])
      swap(num[i-1], num[j]);
    }
    reverse(num.begin()+i, num.end());
  }
};
