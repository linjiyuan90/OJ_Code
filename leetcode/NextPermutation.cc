class Solution {
public:
  void nextPermutation(vector<int> &num) {
    int n = num.size();
    // find the last a[i-1] < a[i] >= a[i+1] >= a[i+2] ...
    int i;
    for (i = n - 1; i > 0; --i) {
      if (num[i-1] < num[i]) {
	break;
      }   
    }
    if (i == 0) {
      std::reverse(num.begin(), num.end());
      return;
    }
    std::reverse(num.begin() + i, num.end());
    int j = std::upper_bound(num.begin() + i, num.end(), num[i-1]) - num.begin();
    std::swap(num[i-1], num[j]);
  }
};
