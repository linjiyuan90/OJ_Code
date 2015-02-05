class Solution {
public:
  //  O(nlogn)
  int maxArea(vector<int> &height) {
    int n = height.size();
    std::vector<std::pair<int, int>> height_with_ix(n);
    for (int i = 0; i < n; ++i) {
      height_with_ix[i] = {height[i], i};
    }
    std::sort(height_with_ix.begin(), height_with_ix.end(), std::greater<std::pair<int, int>>());
    int left = n, right = -1;
    int ans = 0;
    for (std::pair<int, int>& p : height_with_ix) {
      left = std::min(left, p.second);
      right = std::max(right, p.second);
      ans = std::max(ans, (right - left) * p.first);
    }
    return ans;
  }

  // O(n) can be achieved with two deques
  // Intution: choose lefter and larger as left line, righter and larger as right line.
  // One from left to right, increasing; one from right to left, increasing
  int maxArea(std::vector<int>& height) {
    std::size_t n = height.size();
    std::deque<std::pair<int, int>> left, right;
    for (std::size_t i = 0; i < n; ++i) {
      if(left.empty() || left.back().second < height[i]) {
        left.push_back({i, height[i]});
      }
    }
    for (int i = n-1; i >= 0; --i) {
      if(right.empty() || right.back().second < height[i]) {
        right.push_back({i, height[i]});
      }
    }
    int ans = 0;
    while(!left.empty() && !right.empty()) {
      ans = std::max(ans, 
                     std::min(left.front().second, right.front().second) * (right.front().first - left.front().first));
      if (left.front().second < right.front().second) {
        left.pop_front();
      } else {
        right.pop_front();
      }
    }
    return ans;
  }
};
