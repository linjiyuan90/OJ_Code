// O(n)
// maintain a monotanically increasing deque
class Solution {
public:
  int largestRectangleArea(std::vector<int> &height) {
    int ans = 0, n = height.size();
    std::deque<std::pair<int, int>> dq;
    for (int i = 0; i < n; ++i) {
      // leftest index that with height >= height[i]
      auto p = std::make_pair(i, height[i]);
      while (!dq.empty() && dq.back().second >= height[i]) {
	ans = std::max(ans, (i-dq.back().first)*dq.back().second);
	p.first = dq.back().first;
	dq.pop_back();
      }
      dq.push_back(p);
    }
    // deal with left elements
    while(!dq.empty()) {
      ans = std::max(ans, (n - dq.back().first)*dq.back().second);
      dq.pop_back();
    }
    return ans;
  }
};


// Another O(n) approach
// https://github.com/Dionysus1227/edocteel/blob/master/Largest%20Rectangle%20in%20Histogram.cc
// Calculate each i's left, right
// Keep property that height[j] >= height[i], left[i] < j < right[i]
class Solution {
public:
  int largestRectangleArea(std::vector<int> &height) {
    int n = height.size();
    std::vector<int> left(n), right(n);
    for (int i = 0; i < n; ++i) {
      left[i] = i-1;
      while (left[i] != -1 && height[left[i]] >= height[i]) {
	left[i] = left[left[i]]; // nice jump!
      }
    }
    for (int i = n - 1; i >=0; --i) {
      right[i] = i+1;
      while (right[i] != n && height[right[i]] >= height[i]) {
	right[i] = right[right[i]];
      }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans = std::max(ans, (right[i] - left[i] - 1)*height[i]);
    }
    return ans;
  }
};
