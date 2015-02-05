class Solution {
public:
  int largestRectangleArea(vector<int> &height) {
    int n = height.size();
    std::vector<int> left(n), right(n);
    for (int i = 0; i < n; ++i) {
      for (left[i] = i - 1; left[i] != -1 && height[left[i]] >= height[i]; ) {
	left[i] = left[left[i]];
      }
    }
    for (int i = n-1; i >= 0; --i) {
      for (right[i] = i + 1; right[i] != n && height[right[i]] >= height[i]; ) {
	right[i] = right[right[i]];
      }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans = std::max(ans, (right[i] - left[i] - 1) * height[i]);
    }
    return ans;
  }
};
